<?php

/**
 * Nodes sort page form.
 * @param <type> $form
 * @param <type> $form_state
 * @param <type> $nodes
 * @return <type>
 */
function scs_sort_nodes($form, &$form_state, $nodes = array()) {

  if (!empty($_GET['scs_nodes'])) {
    $nodes = explode('-', check_plain($_GET['scs_nodes']));
  }
  if (!empty($_GET['types_order'])) {
    $types = explode('-', check_plain($_GET['types_order']));
  }
  if (count($nodes) == 0) {
    drupal_set_message(t('There was an error. No nodes found'));
    return array();
  }

  //load nodes
  $loaded_nodes = node_load_multiple($nodes);
  // order node by type
  foreach ($loaded_nodes as $key => &$node) {
    $grouped_nodes[$node->type][$key] = $node;
  }

  //save nodes array for future steps
  $form['scs_nodes'] = array('#type' => 'value', '#value' => $grouped_nodes);
  $form['types_order'] = array('#type' => 'value', '#value' => $types);

  $form['newsletter_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Title'),
      '#description' => t('Enter the title of this newsletter'),
      '#default_value' => variable_get('scs_default_title', ''),
      '#required' => true,
  );

  $form['newsletter_term'] = array(
      '#type' => 'radios',
      '#title' => t('Newsletter category'),
      '#required' => true,
      '#options' => simplenews_get_categories(),
  );

  $form['weight'] = array();
  $counter = 0;
  foreach ($nodes as $nid) {
    $form['weight'][$nid] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#title_display' => 'invisible',
        '#delta' => 12,
        '#default_value' => $counter,
        '#attributes' => array('class' => array('scs-node-weight')),
    );

    $counter++;
  }

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create newsletter'),
  );
  return $form;
}

/**
 * Submit handler for the sort nodes form.
 * @param <type> $form
 * @param <type> $form_state
 */
function scs_sort_nodes_submit($form, &$form_state) {
  $form_nodes = array();
  foreach ($form_state['values']['scs_nodes'] as $type => $nodes) {
    foreach ($nodes as $nid => $node) {
      $form_nodes[$type][$nid] = $form_state['values'][$nid];
    }
  }
  $nids = array();
  foreach ($form_nodes as $type => $nodes) {
    asort($form_nodes[$type]);
    $nids = array_merge($nids, array_keys($form_nodes[$type]));
  }
  _scs_create_newsletter($form_state['values']['newsletter_title'],
          $nids,
          $form_state['values']['newsletter_term'],
          $form_state['values']['types_order']);
}

/**
 * Choose nodes page form.
 * @return <type>
 */
function scs_choose_nodes() {

  // Enable language column if translation module is enabled or if we have any
  // node with language.
  $multilanguage = (module_exists('translation') || db_query_range("SELECT 1 FROM {node} WHERE language <> :language", 0, 1, array(':language' => LANGUAGE_NONE))->fetchField());

  // Build the sortable table header.
  $header = array(
      'title' => array('data' => t('Title'), 'field' => 'n.title'),
      'type' => array('data' => t('Type'), 'field' => 'n.type'),
      'author' => t('Author'),
      //'status' => array('data' => t('Status'), 'field' => 'n.status'),
      'changed' => array('data' => t('Updated'), 'field' => 'n.changed', 'sort' => 'desc')
  );
  if ($multilanguage) {
    $header['language'] = array('data' => t('Language'), 'field' => 'n.language');
  }

  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');

  // get newsletter types
  $types = node_type_get_types();
  foreach ($types as $type) {
    $option_types[$type->type] = $type->type;
  }
  $newsletter_types = variable_get('scs_content_types', $option_types);

  $form['newsletter_types']['#value'] = $newsletter_types;
  $query->condition('n.type', $newsletter_types);

  $nids = $query
                  ->fields('n', array('nid'))
                  ->limit(50)
                  ->orderByHeader($header)
                  ->execute()
                  ->fetchCol();
  $nodes = node_load_multiple($nids);

  // Prepare the list of nodes.
  $languages = language_list();
  $destination = drupal_get_destination();
  $options = array();
  foreach ($nodes as $node) {
    $l_options = $node->language != LANGUAGE_NONE && isset($languages[$node->language]) ? array('language' => $languages[$node->language]) : array();
    $options[$node->nid] = array(
        'title' => array(
            'data' => array(
                '#type' => 'link',
                '#title' => $node->title,
                '#href' => 'node/' . $node->nid,
                '#options' => $l_options,
                '#suffix' => ' ' . theme('mark', array('type' => node_mark($node->nid, $node->changed))),
            ),
        ),
        'type' => check_plain(node_type_get_name($node)),
        'author' => theme('username', array('account' => $node)),
        //'status' => $node->status ? t('published') : t('not published'),
        'changed' => format_date($node->changed, 'short'),
    );
    if ($multilanguage) {
      if ($node->language == LANGUAGE_NONE || isset($languages[$node->language])) {
        $options[$node->nid]['language'] = $node->language == LANGUAGE_NONE ? t('Language neutral') : t($languages[$node->language]->name);
      } else {
        $options[$node->nid]['language'] = t('Undefined language (@langcode)', array('@langcode' => $node->language));
      }
    }
  }

  $form['nodes'] = array(
      '#type' => 'tableselect',
      '#header' => $header,
      '#options' => $options,
      '#prefix' => '<div class="form-item"><label>' .
      t('Choose the nodes that you want to include in the newsletter') .
      '</label></div>',
      '#empty' => t('No content available.'),
  );

  $form['weight'] = array();
  $counter = 0;
  foreach ($newsletter_types as $tid => $type) {
    if ($type) {
      $form['weight'][$tid] = array(
          '#type' => 'weight',
          '#title' => t('Weight'),
          '#title_display' => 'invisible',
          '#default_value' => $counter,
          '#delta' => 12,
          '#attributes' => array('class' => array('scs-type-weight')),
      );

      $counter++;
    }
  }

  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Create newsletter'),
      '#submit' => array('scs_choose_nodes_submit'),
  );

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

/**
 * Validate handler for the choose nodes form.
 * @param <type> $form
 * @param <type> $form_state
 */
function scs_choose_nodes_validate($form, &$form_state) {
  // get selected nodes
  foreach ($form_state['values']['nodes'] as $nid => $node) {
    if (!$node) {
      unset($form_state['values']['nodes'][$nid]);
    }
  }

  if(empty($form_state['values']['nodes'])) {
    form_set_error('', t('You have to choose at least one node.'));
  }
}

/**
 * Submit handler for the choose nodes form.
 * @param <type> $form
 * @param <type> $form_state
 */
function scs_choose_nodes_submit($form, &$form_state) {

  // get newsletter types
  $types = node_type_get_types();
  foreach ($types as $type) {
    $option_types[$type->type] = $type->type;
  }
  $newsletter_types = variable_get('scs_content_types', $option_types);
  foreach ($newsletter_types as $type => $value) {
    if ($value) {
      $newsletter_types[$type] = $form_state['values'][$type];
    } else {
      unset($newsletter_types[$type]);
    }
  }
  // order newsletter types
  asort($newsletter_types);
  $newsletter_types = array_keys($newsletter_types);

  // arguments to pass
  $query = array('scs_nodes' => implode('-', $form_state['values']['nodes']),
      'types_order' => implode('-', $newsletter_types));
  drupal_goto('admin/content/scs_sort_nodes', array('query' => $query));
}