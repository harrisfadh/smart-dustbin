var table_body = document.getElementById("table_body");

var table_history = firebase.database().ref().child("dustbin_history");
table_history.on('value', function(snapshot){
	snapshot.forEach(function(childSnapshot){
		var childKey = childSnapshot.key;
		table_body.append(childKey);
		var row = table_body.insertRow();
		//var array_one = dtc3.childElementCount;
		//d1Array.innerText = array_one;
	})
})

function logout(){
		var c = confirm("Confirm sign out?");
	if(c == true){
	auth.signOut();	//logout (firebase authentication)
	window.location.href = "index.html";
	}
	else{
	window.location.href = "main.html"	
	}
}