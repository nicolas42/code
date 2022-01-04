https://eloquentjavascript.net/15_event.html

document.querySelector('span').innerHTML = "Available functions" + (function(){ let o=[];  Object.getOwnPropertyNames(Math).forEach(function(a){o.push(" "+a)});  return o.toString(); })();

window.addEventListener("keydown", event => {
    console.dir(event.key);
});


// Put this at the end of the document (after the textarea) to autosize the element found by the query selector
<script src='autosize.js'></script>
<script>
    autosize(document.querySelector('textarea'));
</script>


// Test the calculator app by copying this into its textarea

23423
"hello this is a thing isnt it"
x=2
y = x^2 + 3 + 4 - 5
2*234
a={x:2,y:3,z:0}
a.z = sqrt(a.x * a.y)
a.z.toString().slice(0,5)
y
