<?php
$defaults = macro_themes_settings('flickr');
$args = macro_themes_params($params,
  array('width' => '\d+'),
  array('width' => 'default'));
    

if( $args['width'] == 'default' || $args['width'] < 100 ) {
  $width  = $defaults['width'];
}
else {
  $width  = $args['width'];
}

$aspect_ratio = 4/3;
$height = round($width / $aspect_ratio);

// Currently we only support display of flickr photosets
preg_match('#/sets/(\d{8,})#', $url, $match);
$setid = $match[1];
?>
<center><object width=<?php print $width ?> height=<?php print $height ?>>
<param name=flashvars value="offsite=true&lang=en-us&page_show_url=<?php print $url ?>%2Fshow%2F&page_show_back_url=<?php print $url ?>%2F&set_id=<?php print $setid ?>&jump_to=">
<param name=movie value="http://www.flickr.com/apps/slideshow/show.swf?v=71649">
<param name=allowFullScreen value=true>
<embed type="application/x-shockwave-flash" src="http://www.flickr.com/apps/slideshow/show.swf?v=71649" allowFullScreen=true flashvars="offsite=true&lang=en-us&page_show_url=<?php print $url ?>%2Fshow%2F&page_show_back_url=<?php print $url ?>%2F&set_id=<?php print $setid ?>&jump_to=" width=<?php print $width?> height=<?php print $height ?>></embed>
</object></center>
