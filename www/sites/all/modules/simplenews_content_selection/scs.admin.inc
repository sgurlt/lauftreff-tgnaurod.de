<?php

/**
 * Admin settings form.
 * @return <type>
 */
function scs_admin_settings_form() {
  $form = array();

  $form['scs_content_view_mode'] = array(
      '#type' => 'select',
      '#title' => t('View mode'),
      '#description' => t('Select the view mode that will be used for nodes rendering.'),
      '#options' => _scs_get_node_view_modes(),
      '#default_value' => variable_get('scs_content_view_mode', array('newsletter')),
  );

  $form['scs_format'] = array(
      '#type' => 'radios',
      '#title' => t('Newsletter format'),
      '#description' => t('Select the format of the newsletters you want to send'),
      '#options' => array('plain' => t('Plain'), 'html' => t('HTML')),
      '#default_value' => variable_get('scs_format', 'html'),
  );

  $form['scs_publish_default'] = array(
      '#type' => 'select',
      '#title' => t('Default publish setting for created newsletters'),
      '#description' => t('Change this select to unpublished if you want to not publish the newsletter node at creation.'),
      '#options' => array(
          0 => t('Unpublished'),
          1 => t('Published'),
      ),
      '#default_value' => variable_get('scs_publish_default', 1),
  );

  $form['scs_default_title'] = array(
      '#type' => 'textfield',
      '#title' => t('Default title for created newsletters'),
      '#description' => t('If filled, this title will be used to populate "title" field when creating a newsletter.'),
      '#default_value' => variable_get('scs_default_title', ''),
  );

  // get content types
  $types = node_type_get_types();
  foreach ($types as $type) {
    $option_types[$type->type] = $type->type;
  }
  // remove newsletter content types
  $simplenews_types = simplenews_get_content_types();
  foreach($simplenews_types as $type) {
    unset($option_types[$type]);
  }

  $form['scs_content_types'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Content types used in newsletters'),
      '#description' => t('Choose the content types you want to use.'),
      '#options' => $option_types,
      '#default_value' => variable_get('scs_content_types', $option_types),
  );

  return system_settings_form($form);
}
