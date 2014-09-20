<?php

$style = theme_get_setting('style');

switch ($style) {
	case 1:
		drupal_add_css(drupal_get_path('theme', 'marine') . '/css/style1.css', array('group' => CSS_THEME, 'weight' => 100, 'type' => 'file'));
		break;
	case 2:
		drupal_add_css(drupal_get_path('theme', 'marine') . '/css/style2.css', array('group' => CSS_THEME, 'weight' => 100, 'type' => 'file'));
		break;
	case 3:
		drupal_add_css(drupal_get_path('theme', 'marine') . '/css/style3.css', array('group' => CSS_THEME, 'weight' => 100, 'type' => 'file'));
		break;
	case 4:
		drupal_add_css(drupal_get_path('theme', 'marine') . '/css/style4.css', array('group' => CSS_THEME, 'weight' => 100, 'type' => 'file'));
		break;
	case 5:
		drupal_add_css(drupal_get_path('theme', 'marine') . '/css/style5.css', array('group' => CSS_THEME, 'weight' => 100, 'type' => 'file'));
		break;
	default:
		drupal_add_css(drupal_get_path('theme', 'marine') . '/css/style1.css', array('group' => CSS_THEME, 'weight' => 100, 'type' => 'file'));

}


/* First and Last Classes on Teasers */

function marine_preprocess_page(&$variables) {
  $nodes = $variables['page']['content']['system_main']['nodes'];
  $i = 1;
  $len = count($nodes);
  foreach (array_keys($nodes) as $nid) {
    if ($i == 1) {
      $variables['page']['content']['system_main']['nodes'][$nid]['#node']->classes_array = array('first');
    }
    if ($i == $len - 1) {
      $variables['page']['content']['system_main']['nodes'][$nid]['#node']->classes_array = array('last');
    }
    $i++;
    /* So I don't get "Warning: Cannot use a scalar value as an array" */
    unset($nodes,$nid);
  }
}

function marine_preprocess_node(&$variables) {
  $node = $variables['node'];
  if (!empty($node->classes_array)) {
    $variables['classes_array'] = array_merge($variables['classes_array'], $node->classes_array);
  }
}

/* Breadcrumbs */

function marine_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Adding the title of the current page to the breadcrumb.
    $breadcrumb[] = drupal_get_title();
   
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<span class="you-are-here">' . t('You are here: ') . '</span>';

    $output .= '<div class="breadcrumb"><div class="breadcrumb-inner">' . implode(' / ', $breadcrumb) . '</div></div>';
    return $output;
  }
}
