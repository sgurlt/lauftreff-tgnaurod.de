(function ($) {

    $(document).ready(function(){															 

	  if ($.browser.msie) { } else {
		$('ul.menu').mobileMenu({
		combine: true,
		switchWidth: 760,
		prependTo: "header",
		nested: false,
		groupPageText: 'More',
		topOptionText: 'Select a page'
		});
	  }
	
    }); 

 	Drupal.behaviors.bonesSuperfish = {
	
	  attach: function(context, settings) {
			  
	  $('#main-menu ul.menu', context).superfish({
		  delay: 400,											    
		  animation: {height:'show' },
		  speed: 500,
		  easing: 'easeOutBounce', 
		  autoArrows: false,
		  dropShadows: false /* Needed for IE */
	  });
		  
	  }
    }	
				
	$(function() {
		
		$('.postscript-wrapper img').hover(function() {
		  $(this).animate({
			  backgroundColor: "#2998B4", opacity: "1.0"
		  }, 'fast'); }, function() {
		  $(this).animate({
			  backgroundColor: "#555", opacity: "0.9"
		  }, 'normal');
		});
	
	});

        $(function() {

                $('.bildergalerie-view-script img').hover(function() {
                  $(this).animate({
                          backgroundColor: "#2998B4", opacity: "1.0"
                  }, 'fast'); }, function() {
                  $(this).animate({
                          backgroundColor: "#555", opacity: "0.9"
                  }, 'normal');
                });

        });

        $(function() {

                $('.abteilungsvorstand-script img').hover(function() {
                  $(this).animate({
                          backgroundColor: "#2998B4", opacity: "1.0"
                  }, 'fast'); }, function() {
                  $(this).animate({
                          backgroundColor: "#555", opacity: "0.9"
                  }, 'normal');
                });

        });
		



})(jQuery);  
