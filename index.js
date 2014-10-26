//<script type="text/javascript">  //I supect I don't need this in a .js file
  WebFontConfig = {
    google: { families: [ 'Londrina+Outline::latin' ] }
  };
  (function() {
    var wf = document.createElement('script');
    wf.src = ('https:' == document.location.protocol ? 'https' : 'http') +
      '://ajax.googleapis.com/ajax/libs/webfont/1/webfont.js';
    wf.type = 'text/javascript';
    wf.async = 'true';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(wf, s);
  })(); 
  //</script>

  console.log("Is this thing on?? Test 1 2 3");