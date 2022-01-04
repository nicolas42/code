function make_calculator(el){

    el.addEventListener("keyup", event => {

        let textarea, p, result, input;

        textarea = el.querySelector('textarea');
        p = el.querySelector('p');

        // replace ^ with ** for powers
        input = textarea.value.replace(/\^/g, "**")
        result = eval(input);
        p.innerHTML = "= "+result.toString();

    })
};
