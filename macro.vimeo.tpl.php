<?php
$defaults = macro_themes_settings('vimeo');
$args = macro_themes_params($params,
  array('width' => '\d+'),
  array('width' => 'default'));
    

if( $args['width'] == 'default' || $args['width'] < 100 ) {
  $width  = $defaults['width'];
}
else {
  $width  = $args['width'];
}

$aspect_ratio = 500/281;
$height = round($width / $aspect_ratio);

$url = "http://vimeo.com/moogaloop.swf?clip_id=$key&server=vimeo.com&show_title=1&show_byline=1&show_portrait=0&color=fee519&fullscreen=1";
?>
<center><object width="<?php print $width ?>" height="<?php print $height ?>">
<param name="allowfullscreen" value="true"></param>
<param name="allowscriptaccess" value="always"></param>
<param name="movie" value="<?php print $url ?>"></param>
<embed src="<?php print $url ?>" type="application/x-shockwave-flash" allowfullscreen="true" allowscriptaccess="always" width="<?php print $width ?>" height="<?php print $height ?>"></embed>
</object></center>
