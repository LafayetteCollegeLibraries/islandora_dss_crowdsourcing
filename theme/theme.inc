<?php

  /**
   * @file Implements theming hooks for the Metadata Crowdsourcing Module
   * @author griffinj@lafayette.edu
   *
   */

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
