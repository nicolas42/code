function showHide(id){
	// show hide block element
	// REQUIRES that <el>.style.display be initialized to
	// "none" or "block" to work properly

	it = document.getElementById(id);
	if (it.style.display === "block"){
		it.style.display = "none";
	} else {
		it.style.display = "block";
	}
}