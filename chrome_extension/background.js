chrome.browserAction.onClicked.addListener(function(tab) {
  chrome.tabs.executeScript(
    null,
    {code: "var scriptElement = document.createElement('script');" +
            "scriptElement.type = 'text/javascript';" +
            "scriptElement.text = \"function googleTranslateElementInit() {" +
            "  new google.translate.TranslateElement({pageLanguage: 'en', layout: google.translate.TranslateElement.InlineLayout.SIMPLE}, 'body');" +
            "}\";" +
            "document.body.appendChild(scriptElement);" +
            "var scriptElement2 = document.createElement('script');" +
            "scriptElement2.type = 'text/javascript';" +
            "scriptElement2.src = '//translate.google.com/translate_a/element.js?cb=googleTranslateElementInit';" +
            "document.body.appendChild(scriptElement2);"}
  );
});
