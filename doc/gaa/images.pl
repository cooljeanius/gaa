# LaTeX2HTML 2008 (1.71)
# Associate images original text with physical files.


$key = q/rightarrow;MSF=1.6;AAT/;
$cached_env_img{$key} = q|<IMG
 WIDTH="20" HEIGHT="14" ALIGN="BOTTOM" BORDER="0"
 SRC="|."$dir".q|img1.png"
 ALT="$\rightarrow$">|; 

$key = q/>;MSF=1.6;AAT/;
$cached_env_img{$key} = q|<IMG
 WIDTH="17" HEIGHT="30" ALIGN="MIDDLE" BORDER="0"
 SRC="|."$dir".q|img3.png"
 ALT="$&gt;$">|; 

$key = q/<;MSF=1.6;AAT/;
$cached_env_img{$key} = q|<IMG
 WIDTH="17" HEIGHT="30" ALIGN="MIDDLE" BORDER="0"
 SRC="|."$dir".q|img2.png"
 ALT="$&lt;$">|; 

1;

