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

