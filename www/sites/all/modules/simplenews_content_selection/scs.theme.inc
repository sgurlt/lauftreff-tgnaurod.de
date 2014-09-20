<?php

/**
 * @file
 * Select Drupal content to create a newsletter
 */

/**
 * Each selected node goes true this function to create a nice body.
 */
function theme_scs_node_output($variables) {
  $output = '';
  $node = $variables['node'];

  $build = node_view($node, $variables['view_mode']);
  unset($build['#contextual_links']); //remove the edit link and etc.

  $output = '<div id="newsletter_node_' . $node->nid . '">';
  $output .= '<div>' . drupal_render($build) . '</div>';
  $output .= '</div>';
  return $output;
}

/**
 * Nodes output is wrapped through this theme.
 * @param <type> $variables
 * @return string
 */
function theme_scs_nodes_output($variables) {

  // order node by type
  foreach ($variables['builds'] as $key => &$entry) {
    $grouped_nodes[$entry['#bundle']][$key] = $entry;
  }

  $output = '';
  $output = '<div id="newsletter-nodes">';
  foreach ($variables['types_order'] as $type) {
    if (!empty($grouped_nodes[$type])) {
      $output .= '<h3>' . node_type_get_name($type) . 's</h3>';
      foreach ($grouped_nodes[$type] as $node) {
        $output .= drupal_render($node);
      }
    }
  }
  $output .= '</div>';
  return $output;
}

/**
 * Chooses nodes form theme.
 * @param <type> $variables
 * @return <type>
 */
function theme_scs_choose_nodes($variables) {
  drupal_add_tabledrag('scs-type-sort-table', 'order', 'sibling', 'scs-type-weight');

  $header = array(t('Type'), t('Weight'));
  $rows = array();
  $newsletter_types = $variables['form']['newsletter_types']['#value'];

  $output = '';

  //build table
  foreach ($newsletter_types as $tid => $type) {
    if ($type) {
      $row = array();
      $row[] = node_type_get_name($type);

      $row[] = drupal_render($variables['form']['weight'][$tid]);
      $row = array('data' => $row);
      $row['class'][] = 'draggable';
      $rows[] = $row;
    }
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('There are no items for display'), 'colspan' => '2'));
  }

  $variables['form']['order_types'] = array(
      '#type' => 'markup',
      '#title' => 'Order types',
      '#weight' => -10,
      '#markup' => '<div class="form-item"><label>' .
      t('Define the order that you want content types to show in the newsletter') .
      '</label></div>' .
      theme('table', array(
          'header' => $header,
          'rows' => $rows,
          'attributes' => array('id' => 'scs-type-sort-table'))),
  );

  $output .= drupal_render($variables['form']['order_types']);
  $output .= drupal_render_children($variables['form']);

  return $output;
}

/**
 * Sort nodes form theme.
 * @param <type> $variables
 * @return <type>
 */
function theme_scs_sort_nodes($variables) {
  $form = $variables['form'];

  $output = '';
  $output .= drupal_render($form['newsletter_title']);

  $nids = $form['scs_nodes']['#value'];
  $types = $form['types_order']['#value'];

  foreach ($types as $type) {

    if (!empty($nids[$type])) {
      $output .= '<div class="form-item"><label>' .
              t('Order !type', array('!type' => node_type_get_name($type))) .
              's</label></div>';
      drupal_add_tabledrag('scs-node-sort-table-' . $type, 'order', 'sibling', 'scs-node-weight');

      $header = array(t('Title'), t('Weight'));
      $rows = array();

      //build table
      foreach ($nids[$type] as $node) {

        $row = array();
        $row[] = $node->title;

        $row[] = drupal_render($form['weight'][$node->nid]);
        $row = array('data' => $row);
        $row['class'][] = 'draggable';
        $rows[] = $row;
      }
      if (empty($rows)) {
        $rows[] = array(array('data' => t('There are no items for display'), 'colspan' => '2'));
      }

      $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'scs-node-sort-table-' . $type)));
    }
  }

  $output .= drupal_render_children($form);

  return $output;
}

/**
 * Theme function to add the titles of the selected nodes at top of the newsletter
 */
function theme_scs_node_titles($variables) {
  return implode("\n", $variables['titles']);
}

/**
 * Theme a complete newsletter.
 * @param <type> $variables
 * @return <type>
 */
function theme_scs_newsletter_output($variables) {
  $body = '';
  $titles = array();
  $builds = array();

  // Node information
  foreach ($variables['nodes'] as $node) {

    unset($node->field_tags);
    $builds[$node->nid] = node_view($node, $variables['view_mode']);

    unset($builds[$node->nid]['#contextual_links']); //remove the edit link and etc.
    unset($builds[$node->nid]['links']); //remove node links
  }

  $body .= theme('scs_nodes_output', array('builds' => $builds,
              'types_order' => $variables['types_order']));
  // Complete newsletter body
  return $body;
}