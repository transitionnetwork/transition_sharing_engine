<?php
// $Id: FeedsViewParser.inc,v 1.17 2010/08/12 10:40:29 adityakg Exp $

/**
 * @file Implementation of View Parser plugin
 */

/**
 * Parses the view output (in JSON).
 * @package feeds
 * @author aditya
 */
class FeedDirectoryParser extends FeedsParser {

  /**
   * Implementation of FeedsParser::parse().
   */
  public function parse(FeedsImportBatch $batch, FeedsSource $source) {
    $raw = trim($batch->getRaw());
    $array = json_decode($raw, TRUE);

    if (!is_array($array)) {
      $raw = preg_replace('/}\s*{/', '},{', $raw);
      $raw = '[' . $raw . ']';
      $array = json_decode($raw, TRUE);
    }

    if (is_array($array)) {
      $source_config = $source->getConfigFor($this);
      if ($array['feeds']) {
        $all_items = $array['feeds'];
        unset($array);
        foreach ($all_items as $item) {
          $batch->addItem($item['feed']);
        }
      }
      //watchdog('Sharing Engine', 'batch: ' . print_r($batch, true));
    }
    else {
      throw new Exception(t('There was an error decoding the JSON document.'));
    }
  }


  /**
  * Override parent::getMappingSources().
  */
  public function getMappingSources() {
    return array(
      'source_title' => array(
        'name' => t('Source: Title'),
        'description' => t('The name of the directory entry.'),
        ),
      'source_url' => array(
        'name' => t('Source: Directory URL'),
        'description' => t('The url of the directory entry.'),
        ),
      'source_feed_guid' => array(
        'name' => t('Source: GUID'),
        'description' => t('A GUID for this feed for this entity (NOT feed source URL).'),
        ),
      'source_updated' => array(
        'name' => t('Source: Updated'),
        'description' => t('The date and time the directory entry was last updated.'),
        ),
      'source_feed' => array(
        'name' => t('Source: Feed'),
        'description' => t('The feed URL (RSS/ATOM source) of the directory entry.'),
        ),
      'location_street' => array(
        'name' => t('Location: Street'),
        'description' => t('The street address for the directory entity.'),
        ),
      'location_city' => array(
        'name' => t('Location: City'),
        'description' => t('The city for the directory entity.'),
        ),
      'location_province' => array(
        'name' => t('Location: Province'),
        'description' => t('The province/state for the directory entity.'),
        ),
      'location_postcode' => array(
        'name' => t('Location: Postcode'),
        'description' => t('The postcode for the directory entity.'),
        ),
      'location_country_code' => array(
        'name' => t('Location: Country code'),
        'description' => t('The 2-digit country code for the directory entity.'),
        ),
      'location_country_name' => array(
        'name' => t('Location: Country name'),
        'description' => t('The country name for the directory entity.'),
        ),
      'location_latitude' => array(
        'name' => t('Location: Latitude'),
        'description' => t('The decimal latitdue for the directory entity.'),
        ),
      'location_longitude' => array(
        'name' => t('Location: Longitude'),
        'description' => t('The decimal longitdue for the directory entity.'),
        ),
    ) + parent::getMappingSources();
  }

  /**
   * Define defaults.
   */
  public function sourceDefaults() {
    return array(
      'context' => '',
      'sources' => array(),
    );
  }

  /**
   * Override parent::sourceFormValidate().
   *
   * Simply trims all JSONPath values from the form. That way when testing them
   * later we can be sure that there aren't any strings with spaces in them.
   *
   * @param &$values
   *   The values from the form to validate, passed by reference.
   */
  /*public function sourceFormValidate(&$values) {
    $values['context'] = trim($values['context']);
    foreach ($values['sources'] as &$query) {
        $query = trim($query);
    }
  }*/


}
