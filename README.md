# Macro Themes #

The Macro Themes module defines a set of functions for theming out rich media
content such as Youtube videos or static images.  You can implement these
themes via the built-in input filter, or through your own code.

The input filter translates "macros" into rich media. For instance, the following
macro will insert a Youtube video:

[youtube http://www.youtube.com/watch?v=tQzbPStmboM]

or simply:

[youtube tQzbPStmboM]


## Installation & Configuration ##

1. Go to admin/build/modules and enable the Macro Themes module

2. Go to admin/build/themes/settings/garland (or your theme) to set default
display options for each recognized macro

3. Go to admin/settings/filters to add the Macro Themes filter to an input format and
change filter settings. The Macro Themes filter typically works best if arranged after
filters that produce HTML output (like HTML Filter or Markdown) and before filters that
transform URLs (like URL filter).


## Macros ##

All macros are enclosed in square brackets and begin with the type of media content to be
displayed.

### [image] ###

The image macro works like this:

[image imagename.png options Your Caption Here]

The image macro displays static image files such as GIF, JPG and PNG images. Absolute and
relative URLs are both supported. Unqualified paths are assumed to be relative to the
site's files directory. This lets users embed images they attach with the Upload module
(you may want to change the default settings for uploaded files so that they are not, by
default, displayed in a list).

The image macro recognizes several options (all optional) in option=setting format
(overriding the defaults set in admin/build/themes):

* width=200 will set the image width to 200 pixels. If the setting is non-numeric, it is
treated as a classname, so that you can define a CSS class such that "width=half" or
"width=third" to set the image width to a percentage of the content area.  See the CSS
file for sample styles, which you may override for your theme.

* framed=yes|no will frame the image

* align=left|right|center|none sets the image alignment

* imagecache=cache will render the image via the specified image cache, if the module
is installed, and if the image is unqualified (that is, in the file system directory).

* id=n sets the id attribute for the image.

* map=mapname sets the usemap attribute on the image. Together with the id setting, this
is typically used to implement imagemaps, which are typically defined elsewhere in the
content area.

* nid=n will hyperlink the image to the specified node.

* popup=yes|no will add the "rel='facebox'" attribute to the image, allowing the image
to display in a popup implemented with the [Facebox](http://defunkt.io/facebox) widget.

#### Examples ####

[image cloud.png align=right]

Embed an image from the file system directory, aligned right

[image http://images.foo.org/cloud.png]

Embed an image on another website

[image cloud.png width=300]

Embed an image scaled to 300px

[image cloud.png width=third align=left]

Embed a left-aligned image, one third the content width (as defined by your CSS)


### [youtube] ###

Youtube video macros look like this:

[youtube http://www.youtube.com/watch?v=tQzbPStmboM options]

or simply:

[youtube tQzbPStmboM options]

Optional options are:

* width=n sets the video width, in pixels

* ratio=normal|wide sets the aspect ratio to either 4:3 (normal) or 16:9 (wide). This
should match the video you are embedding.



### [vimeo] ###

Vimeo video macros are similar:

[vimeo http://vimeo.com/38164075 options]

or simply:

[vimeo 38164075 options]

Optional options are:

* width=n sets the video width, in pixels



### [flickr] ###

Display Flickr photosets like this:

[flickr http://www.flickr.com/photos/timherzog/sets/72157624346396031 options]

Optional options are:

* width=n sets the display width, in pixels
