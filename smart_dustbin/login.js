function login(){
	var u_email = document.getElementById("username");
	var u_password = document.getElementById("password");
	
	const promise = auth.signInWithEmailAndPassword(u_email.value, u_password.value);	//firebase login
	promise.catch(e => alert(e.message));	//catch firebase authentication error
}

auth.onAuthStateChanged(function(user){		//redirect user to main.html if logged in
	if(user){
		window.location.href = "main.html";
	}
	
	else{
	}
});