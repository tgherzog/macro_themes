<?php
  /* See http://wphacks.com/fixing-css-drop-down-menus-hiding-behind-flash-objects for the wmode param */

$defaults = macro_themes_settings('youtube');
$args = macro_themes_params($params,
  array('width' => '\d+', 'ratio' => '(normal|wide)'),
  array('width' => 'default', 'ratio' => $defaults['ratio']));
    

if( $args['width'] == 'default' || $args['width'] < 100 ) {
  $width  = $args['ratio'] == 'wide' ? $defaults['width_wide'] : $defaults['width_normal'];
}
else {
  $width  = $args['width'];
}

$aspect_ratio = $args['ratio'] == 'wide' ? 480/295 : 425/324;
$height = round($width / $aspect_ratio);
$url = "http://www.youtube.com/v/$key&hl=en&fs=1&rel=0&showinfo=0&hd=1";
?>
<center>
<object width="<?php print $width ?>" height="<?php print $height ?>">
<param name="movie" value="<?php print $url ?>"></param>
<param name="allowFullScreen" value="true"></param>
<param name="wmode" value="transparent">
<embed src="<?php print $url ?>" type="application/x-shockwave-flash" allowfullscreen="true" wmode="transparent" width="<?php print $width ?>" height="<?php print $height ?>"></embed>
</object>
</center>
