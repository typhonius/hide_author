<?php

/**
 * @file
 */

function hide_author_admin_page() {
  $header = array(
    'nid' => array('data' => t('NID'), 'field' => 'nid', 'sort' => 'desc'),
    'Title' => array('data' => t('Title'), 'field' => 'nid'),
    'uid' => array('data' => t('User'), 'field' => 'uid'),
  );
  /*$header = array(
    'title' => array('data' => t('Title'), 'field' => 'n.title'),
    'type' => array('data' => t('Type'), 'field' => 'n.type'),
    'author' => t('Author'),
  );
  $header['operations'] = array('data' => t('Operations'));
  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');
*/
  $query = db_select('hide_author', 'ha');
  $query->join('node', 'n', 'ha.nid = n.nid');
  $query->fields('ha', array('nid', 'uid'))
    ->fields('n', array('title'))
    ->extend('PagerDefault')
    ->limit(50)
    ->extend('TableSort')
    ->orderByHeader($header);
  $result = $query->execute();

  $rows = array();
  foreach ($result as $record) {
    $rows[$record->nid]['nid'] = $record->nid;
    $rows[$record->nid]['title'] = $record->title;
    $rows[$record->nid]['uid'] = $record->uid;
  }
 
  $form['rules'] = array(
    '#theme' => 'table',
    '#header' => $header,
    '#rows' => $rows,
    '#empty' => t('There are currently no nodes with a hidden author.'),
  );

  return $form;
}
