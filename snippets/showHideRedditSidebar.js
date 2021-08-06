

// Show/Hide Reddit Sidebar Version 2

var sidebar = document.querySelector('div.side');
sidebar.style.display = 'block';	// sometimes style.display is not defined as something reasonable

function showHideRedditSidebar(){

if (sidebar.style.display === 'block') {
	sidebar.style.display = 'none';
} else if (sidebar.style.display === 'none') {
	sidebar.style.display = 'block';
}

}



showHideRedditSidebar()

el = document.createElement('li')
el.innerHTML = "Hello"



#sr-header-area > div > div.sr-list > ul:nth-child(1)