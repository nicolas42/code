// This script simply runs some code in a particular website.
// The website it'll run it in is defined in the manifest.json file
// You have to use https://domain.com/* or something like that to specify the page
// Alternatively, "matches": ["<all_urls>"], will do all them, I think.

// Anyway, we're injecting this code into chatgpt because chatgpt updated
// itself to where it's too advanced to run on my old macbook.
// We need to use this complicated injection code because by default, it appears, extension code doesn't run in the same namespace as the website.  This fixes it.  Woo...


// tl;dr This script injects this code into chatgpt, equivalent to pasting it into the javascript console.
/*
   if (!Array.prototype.toSorted) {
     Array.prototype.toSorted = function(compareFn) {
       return Array.from(this).sort(compareFn);
     };
   }
*/


function injectScript(source) {
  const script = document.createElement('script');
  script.textContent = source;
  (document.head || document.documentElement).appendChild(script);
  script.remove();
}

const codeToInject = `
if (!Array.prototype.toSorted) {
  Array.prototype.toSorted = function(compareFn) {
    return Array.from(this).sort(compareFn);
  };
  console.log('Array.prototype.toSorted polyfill added.');
} else {
  console.log('Array.prototype.toSorted already exists.');
}
`;

window.addEventListener('load', function() {
    injectScript(codeToInject);
});

