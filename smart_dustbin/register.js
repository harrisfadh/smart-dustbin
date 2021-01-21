//retrieve input value from maintenance.html

var u_name = document.getElementById("name");
var u_email = document.getElementById("username");
var u_password = document.getElementById("password");

function register(){

firebase.auth().createUserWithEmailAndPassword(u_email.value, u_password.value).then(function(){	//firebase authentication sign up function
	
	var firebase_name = firebase.database().ref().child("User/" + u_name.value + "/Name");	//referring to firebase database child node
	firebase_name.set(u_name.value);	//set value to child node
	
	var firebase_email = firebase.database().ref().child("User/" + u_name.value + "/Email");	//referring to firebase database child node
	firebase_email.set(u_email.value);	//set value to child node
	
	var firebase_password = firebase.database().ref().child("User/" + u_name.value + "/Password");	//referring to firebase database child node
	firebase_password.set(u_password.value);	//set value to child node
	
	window.alert("User has been registered successfully");
	window.location.href = "index.html";
	
}).catch(function(error) {	//catch firebase authentication sign up error
  // Handle Errors here.
  var errorCode = error.code;
  var errorMessage = error.message;
  window.alert(errorCode + ". " + errorMessage + ". Please re-enter email and password.");
  // ...
});
}