<?php

/* macro_image: render an [image] macro in the form:
 *
 * [image filename.ext options caption]
 *
 * where options are:
 *  align=none|left|right|center (default: none)
 *  framed=yes|no (default: yes)
 *  width=original|{class-name}|## (default: original)
 *
 * If width is original and the file is local, the original width will be used.
 * If width is a number, it specifies the width in pixels.
 * Otherwise, width is a CSS class that you should define, e.g:
 *
 * div.inline-image.third, div.inline-image.third img { width: 200px; }
 *
 */
function theme_macro_image($image, $caption, $params) {
  $defaults = macro_themes_settings('image');
  $args = macro_themes_params($params,
	array('width' => '\w+', 'imagecache' => '[\w\-]+', 'align' => 'none|left|right|center', 'framed' => 'yes|no', 'id' => '\w+', 'map' => '\w+', 'popup' => 'yes|no', 'nid' => '\d+'),
	array('width' => 'original', 'imagecache' => $defaults['imagecache'], 'align' => $defaults['align'], 'framed' => $defaults['framed'], 'id' => '', 'map' => '', 'popup' => 'no', 'nid' => ''));

  // treat the filename as url-encoded, and decode. So + becomes space, etc
  $image = urldecode($image);

  // convert select encoded characters, so they can put brackets in the caption
  $caption = str_replace(array('%5B', '%5D'), array('[', ']'), $caption);

  $attributes = array('class' => 'inline-image');
  if( $args['align'] != 'none' ) {
    $attributes['class'] .= ' ' . $args['align'];
  }

  $img_attributes = array();
  if( substr($image, 0, 5) == 'http:' ) {
    $local = false;
  }
  elseif( substr($image, 0, 1) == '/' ) {
    // must add host name so theme_image doesn't screw up the path
	global $base_root;
	$image = "$base_root$image";
	$local = false;
  }
  else {
    $image = file_directory_path() . '/' . $image;
	$local = true;
  }

  // sanity check to implement imagecache
  if( ! module_exists('imagecache') || ! $local || $args['imagecache'] == 'none' ) {
    $args['imagecache'] = null;
  }

  if( $args['width'] == 'original' && $local && ! $args['imagecache'] ) {
    list($width) = @getimagesize($image);
	if( $defaults['max_width'] ) {
	  // trim to maximum width, if any
	  $width = min($width, $defaults['max_width']);
	  $img_attributes['width'] = $width;
	}

	$attributes['style'] = "width: {$width}px";
  }
  elseif( is_numeric($args['width']) ) {
    $attributes['style'] = "width: $args[width]px";
	$img_attributes['width'] = $args['width'];
  }
  elseif( $args['width'] != 'original' ) {
    $attributes['class'] .= ' ' . _macro_themes_id_safe($args['width']);
	$img_attributes['class'] = _macro_themes_id_safe($args['width']);
  }

  if( $args['framed'] == 'yes' ) {
    $img_attributes['class'] .= ($img_attributes['class'] ? ' ' : '') . 'framed';
  }

  if( $args['id'] ) {
    $img_attributes['id'] = $args['id'];
  }

  if( $args['map'] ) {
    $img_attributes['usemap'] = '#' . $args['map'];
  }

  // Try to decompile the string, so theme_image won't screw it up
  $caption_ = str_replace(array('&amp;', '&gt;', '&lt;'), array('&', '<', '>'), $caption);
  if( $args['imagecache'] ) {
    $img = theme('imagecache', $args['imagecache'], $image, '', $caption_, $img_attributes, false);
	$attributes['class'] .= ' ' . $args['imagecache'];
  }
  else {
	$img = theme('image', $image, '', $caption_, $img_attributes, false);
  }

  if( $args['popup'] == 'yes' ) {
    $img = l($img, $image, array(
	  'attributes' => array('rel' => 'facebox'),
	  'html' => true,
    ));
  }
  elseif( $args['nid'] ) {
    $img = l($img, 'node/' . $args['nid'], array('html' => true));
  }

  $output = '<div ' . drupal_attributes($attributes) . '>' . $img;
  if( $caption ) {
	// Markdown will already have sanitized our output, so we don't call check_plain here
    $output .= '<span>' . $caption . '</span>';
  }

  $output .= '</div>';
  return $output;
}

function _macro_themes_form_system_theme_settings_alter(&$form) {

  $key = arg(4) ? arg(4) : '';
  $settings = macro_themes_default_settings($key);

  $form['macro_themes'] = array(
	'#type' => 'fieldset',
	'#title' => t('Macro Themes'),
	'#description' => t('Default settings for content macros formatted by the Macro Themes module. In most cases, users can override these defaults in each macro instance.'),
	'#collapsible' => TRUE,
	'#collapsed' => TRUE,
	'#weight' => 0,
  );

  if( ! $key ) {
	// Global settings
	$form['macro_themes']['macro_themes_include_css'] = array(
	  '#type' => 'checkbox',
	  '#title' => t('Include macro_themes.css'),
	  '#description' => t('Select this option to include the macro_themes.css file. If you override most or all of the CSS definitions, you can improve efficiency by deselecting this option. Note this is set at the global level, and applies to all themes.'),
	  '#default_value' => $settings['macro_themes_include_css'],
	);
  }

  $form['macro_themes']['flickr'] = array(
    '#type' => 'fieldset',
	'#title' => t('[flickr] macro default settings'),
	
	'macro_themes_flickr_width' => array(
	  '#type' => 'textfield',
	  '#title' => t('Width'),
	  '#description' => t('Default pixel width for flickr presentations.'),
	  '#size' => 4,
	  '#default_value' => $settings['macro_themes_flickr_width'],
	),
  );

  $form['macro_themes']['image'] = array(
    '#type' => 'fieldset',
	'#title' => t('[image] macro default settings'),
	
	'macro_themes_image_max_width' => array(
	  '#type' => 'textfield',
	  '#title' => t('Maximum width'),
	  '#description' => t('Maximum image width in pixels. Images wider than this will be scaled.'),
	  '#size' => 4,
	  '#default_value' => $settings['macro_themes_image_max_width'],
	),
	
	'macro_themes_image_framed' => array(
	  '#type' => 'checkbox',
	  '#title' => t('Frame images'),
	  '#description' => t('Frame images with a border.'),
	  '#default_value' => $settings['macro_themes_image_framed'],
	  '#return_value' => 'yes',
	),
	
	'macro_themes_image_align' => array(
	  '#type' => 'select',
	  '#title' => t('Alignment'),
	  '#description' => t('Image alignment. Text will wrap around images that are left or right.'),
	  '#default_value' => $settings['macro_themes_image_align'],
	  '#options' => array('none' => t('None'), 'left' => t('Left'), 'right' => t('Right'), 'center' => t('Center')),
	),
  );

  $form['macro_themes']['slideshare'] = array(
    '#type' => 'fieldset',
	'#title' => t('[slideshare] macro default settings'),
	
	'macro_themes_slideshare_width' => array(
	  '#type' => 'textfield',
	  '#title' => t('Width'),
	  '#description' => t('Default pixel width for Slideshare presentations.'),
	  '#size' => 4,
	  '#default_value' => $settings['macro_themes_slideshare_width'],
	),
  );

  $form['macro_themes']['vimeo'] = array(
    '#type' => 'fieldset',
	'#title' => t('[vimeo] macro default settings'),
	
	'macro_themes_vimeo_width' => array(
	  '#type' => 'textfield',
	  '#title' => t('Width'),
	  '#description' => t('Default pixel width for Vimeo videos.'),
	  '#size' => 4,
	  '#default_value' => $settings['macro_themes_vimeo_width'],
	),
  );

  $form['macro_themes']['youtube'] = array(
    '#type' => 'fieldset',
	'#title' => t('[youtube] macro default settings'),
	
	'macro_themes_youtube_ratio' => array(
	  '#type' => 'radios',
	  '#title' => t('Aspect ratio'),
	  '#description' => t('Default aspect ratio for Youtube videos.'),
	  '#options' => array('normal' => t('Classic (4:3)'), 'wide' => t('Widescreen (16:9)')),
	  '#default_value' => $settings['macro_themes_youtube_ratio'],
	),
	'macro_themes_youtube_width_normal' => array(
	  '#type' => 'textfield',
	  '#title' => t('Width for Classic aspect ratio'),
	  '#size' => 4,
	  '#default_value' => $settings['macro_themes_youtube_width_normal'],
	),
	'macro_themes_youtube_width_wide' => array(
	  '#type' => 'textfield',
	  '#title' => t('Width for Widescreen aspect ratio'),
	  '#size' => 4,
	  '#default_value' => $settings['macro_themes_youtube_width_wide'],
	),
  );

  if( module_exists('imagecache') ) {
    $presets = imagecache_presets();
	$options = array('' => 'None');
	foreach(imagecache_presets() as $id => $preset) {
	  $name = $preset['presetname'];
	  $options[$name] = $name;
	}

	$form['macro_themes']['image']['macro_themes_image_imagecache'] = array(
	  '#type' => 'select',
	  '#title' => t('Imagecache'),
	  '#description' => t('Imagecache to use for images.'),
	  '#default_value' => $settings['macro_themes_image_imagecache'],
	  '#options' => $options,
	);
  }
}
