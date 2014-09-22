<?php

  /**
   * @file Implements theming hooks for the Metadata Crowdsourcing Module
   * @author griffinj@lafayette.edu
   *
   */

/**
 * Implements hook_preprocess_theme().
 */
function dss_crowdsourcing_preprocess_islandora_default(&$vars) {

  dpm($vars);
  }

  /**
   * Implements hook_preprocess_theme().
   * @param $vars
   * The variables
   *
   * @see comment_node_page_additions().
   *
   */
function dss_crowdsourcing_preprocess_islandora_book_book(array &$vars) {

  $object = $vars['object'];

  // Append comment form if needed.
  //if (user_access('post comments') && $node->comment == COMMENT_NODE_OPEN && (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW)) {
  if(user_access('post comments')) {
    
    //$build = drupal_get_form("comment_node_{$node->type}_form", (object) array('nid' => $node->nid));
    //$additions['comment_form'] = $build;
    $build = drupal_get_form('dss_crowdsourcing_form', (object) array('object_pid' => $object->id));
    $vars['crowdsourcing'] = drupal_render($build);
  }
}

/**
 * Implements hook_preprocess().
 *
 * @param array $variables
 *   an array of variables that will be passed to the theme function
 */
function dss_crowdsourcing_preprocess_islandora_large_image(&$vars) {

  $vars['template_files'][] = 'islandora-large-image';

  $object = $vars['islandora_object'];

  // Append comment form if needed.
  //if (user_access('post comments') && $node->comment == COMMENT_NODE_OPEN && (variable_get('comment_form_location_' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_BELOW)) {
  //if(user_access('post comments')) {
  if(TRUE) {

    //$build = drupal_get_form("comment_node_{$node->type}_form", (object) array('nid' => $node->nid));
    //$additions['comment_form'] = $build;

    // Is this a GeoTIFF?
    if(module_exists('islandora_gis') and islandora_gis_object_is_georeferenced($object)) {

      /*
	module_load_include('inc', 'node', 'node.pages');
	$node = clone $vars['node'];
	$form = drupal_get_form('mytype_node_form', $node);
       */

      //$build = drupal_get_form('dss_crowdsourcing_gis_form', (object) array('object_pid' => $object->id));

      module_load_include('inc', 'node', 'node.pages');
      $node_form = new stdClass;
      $node_form->type = 'islandora_gis_feature';
      $node_form->language = LANGUAGE_NONE;
      $build = drupal_get_form('islandora_gis_feature_node_form', $node_form);

      $vars['crowdsourcing'] = drupal_render($build);
    } else {

      $build = drupal_get_form('dss_crowdsourcing_form', (object) array('object_pid' => $object->id));
      $vars['crowdsourcing'] = drupal_render($build);
    }
  }
}


function dss_crowdsourcing_form_islandora_gis_feature_node_form_alter(&$form) {

  //dpm($form);

  $form['content_fields'] = array('#type' => 'fieldset',
				  '#title' => 'Specify a Location for this Content',
				  '#collapsible' => TRUE,
				  );

  foreach(array('title', 'field_primary_feature', 'body') as $field_name) {

    if(array_key_exists($field_name, $form)) {

      $form['content_fields'][$field_name] = $form[$field_name];
      hide($form[$field_name]);
    }
  }
}
