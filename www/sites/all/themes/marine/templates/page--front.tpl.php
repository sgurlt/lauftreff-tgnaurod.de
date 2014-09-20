<div id="top">

  <div class="user-menu-wrapper clearfix"><div class="user-menu-wrapper-inner">  
    <nav id="user-menu" class="<?php echo $grid_size ?>">
      <?php print render($page['user_menu']); ?>
    </nav>
  </div></div>
  
  <div class="header-wrapper clearfix"><div class="header-wrapper-inner <?php echo $grid_size ?>">
    <header>
      
      <?php if ($logo): ?>
        <div class="site-logo">
          <a href="<?php print check_url($front_page); ?>"><img src="<?php print $logo ?>" alt="<?php print $site_name; ?>" /></a>
        </div>
      <?php endif; ?>	      
      
      <hgroup>
        <?php if ($site_name): ?>
            <?php if ($is_front) { ?>
              <h1 class="site-name"><a href="<?php print check_url($front_page); ?>"><?php print $site_name; ?></a></h1>
            <?php } else { ?>
              <h2 class="site-name"><a href="<?php print check_url($front_page); ?>"><?php print $site_name; ?></a></h2>
            <?php } ?>
        <?php endif; ?>
        
        <?php if ($site_slogan): ?>
            <h3 class="site-slogan"><?php print $site_slogan; ?></h3>            
        <?php endif; ?>    
      </hgroup>      
       
    </header>
    
    <div class="search-box">
      <?php print render($page['search_box']); ?>
    </div>
    
    <div id="social">
      <ul class="social-links">
        <li><a class="twitter" target="_blank" href="http://www.tg-naurod.de"></li>
        <li><a class="tgn" target="_blank" href="http://www.tg-naurod.de/"></a></li>
        <li><a class="facebook" href="<?php echo $facebook ?>"></a></li>
      </ul>
    </div>         
        
  </div></div>  
  
</div>

<div id="page" class="<?php echo $grid_size ?>">

  <?php if ($page['main_menu']): ?>    
    <div class="main-menu-wrapper clearfix"><div class="main-menu-wrapper-inner">  
      <nav id="main-menu">
        <?php print render($page['main_menu']); ?>
      </nav>
    </div></div> 
  <?php endif; ?>    
  
  <?php if ($page['nav_menu']): ?>    
    <div class="nav-menu-wrapper clearfix"><div class="nav-menu-wrapper-inner">  
      <nav id="nav-menu">
        <?php print render($page['nav_menu']); ?>
      </nav>
    </div></div> 
  <?php endif; ?>    
  
  <?php if ($page['slideshow']): ?>    
    <div class="slideshow-wrapper clearfix"><div class="slideshow-wrapper-inner">  
      <nav id="slideshow">
        <?php print render($page['slideshow']); ?>
      </nav>
    </div></div> 
  <?php endif; ?>
  
  <?php if ($page['preface_1'] || $page['preface_2'] || $page['preface_3'] || $page['preface_4']): ?>   
    <div class="preface-wrapper clearfix"><div class="preface-wrapper-inner">  
      <section id="preface">
        <div class="<?php echo $preface_1_grid_width ?>"><?php print render($page['preface_1']); ?></div>
        <div class="<?php echo $preface_2_grid_width ?>"><?php print render($page['preface_2']); ?></div>
        <div class="<?php echo $preface_3_grid_width ?>"><?php print render($page['preface_3']); ?></div>
        <div class="<?php echo $preface_4_grid_width ?>"><?php print render($page['preface_4']); ?></div>
      </section>
    </div></div> 
  <?php endif; ?>   
  
  <div class="postscript-wrapper clearfix"><div class="postscript-wrapper-inner">  
    <section id="postscript">
      <div class="<?php echo $postscript_1_grid_width ?>"><?php print render($page['postscript_1']); ?></div>
      <div class="<?php echo $postscript_2_grid_width ?>"><?php print render($page['postscript_2']); ?></div>
      <div class="<?php echo $postscript_3_grid_width ?>"><?php print render($page['postscript_3']); ?></div>
      <div class="<?php echo $postscript_4_grid_width ?>"><?php print render($page['postscript_4']); ?></div>
    </section>
  </div></div>    
 
</div><!-- page -->

<!-- All Hail the Footer -->
  <div class="footer-wrapper clearfix"><div class="footer-wrapper-inner">
    <footer id="footer" class="<?php echo $grid_size ?>">
      <?php print render($page['footer']) ?>
      <span style="font-size: 0.6em;">Designed by <a href="http://www.themeshark.com">ThemeShark.com</a></span>
    </footer><!-- /footer -->
  </div></div>
