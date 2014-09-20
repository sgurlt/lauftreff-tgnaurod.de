<article id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
	
  <div class="article-header">  
    
	<?php print $user_picture; ?>
  
    <?php print render($title_prefix); ?>
          
      <?php if (!$page): ?>
        <h2 class="title"<?php print $title_attributes; ?>><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
      <?php endif; ?>
  
      <?php if ($page): ?>
        <h1 class="title"<?php print $title_attributes; ?>><?php print $title; ?></h1>
      <?php endif; ?>
         
    <?php print render($title_suffix); ?>
  
	<?php if (!empty($content['field_tags'])): ?>  
      <nav class="taxonomy"><div class="taxonomy-inner clearfix">
        <?php print render($content['field_tags']); ?>
      </div></nav>  
	<?php endif; ?>
  </div>  
  <div class="content termin-node">
  <table>
	<td width="150px" class="termin-datum-node">
	<b><?php print render($content['field_datum']); ?></b>
	<?php print render($content['field_termin_plz']); ?><?php print render($content['field_termin_ort']); ?>
	<?php print render($content['field_termin_strasse']); ?>
	<?php print render($content['field_termin_typ']); ?>
	</td>		
	<td valign="top" class="termin-beschreibung">
	<?php print render($content['body']); ?>
	</td>
  </table>
  </div>
    
  <?php if (!empty($content['links'])): ?>  
  <nav class="links"><div class="links-inner clearfix">
    <?php print render($content['links']); ?>
  </div></nav>  
  <?php endif; ?>

  <?php print render($content['comments']); ?>

</article> 
