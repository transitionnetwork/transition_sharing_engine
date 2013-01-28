<?php
// $Id: FeedsMetaNodeProcessor.inc,v 1.51.2.2 2010/10/25 22:43:03 alexb Exp $

/**
 * @file
 * Class definition of FeedsMetaNodeProcessor.
 */

// Create or delete FEEDS_NODE_BATCH_SIZE at a time.
define('FEEDS_NODE_BATCH_SIZE', 50);

// Deprecated. Use FEEDS_SKIPE_EXISTING, FEEDS_REPLACE_EXISTNG,
// FEEDS_UPDATE_EXISTING instead.
define('FEEDS_NODE_SKIP_EXISTING', 0);
define('FEEDS_NODE_REPLACE_EXISTING', 1);
define('FEEDS_NODE_UPDATE_EXISTING', 2);

/**
 * Creates nodes from feed items.
 */
class FeedsMetaNodeProcessor extends FeedsNodeProcessor {

  /**
   * Implementation of FeedsProcessor::clear().
   *
   * Overriden to PREVENT deletion of Feed Meta nodes
   */
  public function clear(FeedsBatch $batch, FeedsSource $source) {
    $batch->setProgress(FEEDS_CLEARING, FEEDS_BATCH_COMPLETE);
  }

  /**
   * Override setTargetElement to operate on a target item that is a node.
   */
  public function setTargetElement($target_node, $target_element, $value) {
    parent::setTargetElement($target_node, $target_element, $value);
    if ($target_element  == 'created') {
      $target_node->$target_element = strtotime($value);
    }
  }

}

