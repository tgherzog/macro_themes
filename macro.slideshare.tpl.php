<?php
$defaults = macro_themes_settings('slideshare');
$args = macro_themes_params($params,
  array('width' => '\d+'),
  array('width' => 'default'));
    

if( $args['width'] == 'default' || $args['width'] < 100 ) {
  $width  = $defaults['width'];
}
else {
  $width  = $args['width'];
}

$aspect_ratio = 600/501;
$height = round($width / $aspect_ratio);

$url = "http://static.slideshare.net/swf/ssplayer2.swf?doc=$key&rel=0";
?>
<center>
<object style="margin:0px" width="<?php print $width ?>" height="<?php print $height ?>" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,29,0">
<param name="movie" value="<?php print $url ?>"/>
<param name="allowFullScreen" value="true"/>
<param name="allowScriptAccess" value="always"/>
<embed src="<?php print $url ?>" type="application/x-shockwave-flash" pluginspage="http://www.macromedia.com/go/getflashplayer" allowscriptaccess="always" allowfullscreen="true" width="600" height="501"></embed>
</object></center>
