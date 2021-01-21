var dustbin_status = document.getElementById("dustbin_status");

var today = new Date(); 
var time = today.getDate()+'-'+(today.getMonth()+1)+'-'+today.getFullYear() + " " 
		+ today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();

var empty = firebase.database().ref().child("empty");			//referring to firebase database child node(empty)
empty.on("value", function(datasnapshot){

	e = datasnapshot.val();	//get empty value
	
	if(e == 1){
	dustbin_status.innerHTML = "0%";
	dustbin_status.style.color = "Green";
	}
	
	else{
	}

})

var btm_q = firebase.database().ref().child("btm_quarter");			//referring to firebase database child node(btm_quarter)
btm_q.on("value", function(datasnapshot){

	bq = datasnapshot.val();	//get btm_quarter value
	
	if(bq == 1){
	dustbin_status.innerHTML = "25%";
	dustbin_status.style.color = "Green";
	}
	
	else{
	}

})

var half = firebase.database().ref().child("half");			//referring to firebase database child node(half)
half.on("value", function(datasnapshot){

	h = datasnapshot.val();	//get half value
	
	if(h == 1){
	dustbin_status.innerHTML = "50%";
	dustbin_status.style.color = "Yellow";
	}
	
	else{
	}

})

var upper_quarter= firebase.database().ref().child("upper_quarter");			//referring to firebase database child node(upper_quarter)
upper_quarter.on("value", function(datasnapshot){

	uq = datasnapshot.val();	//get upper_quarter value
	
	if(uq == 1){
	dustbin_status.innerHTML = "75%";
	dustbin_status.style.color = "Orange";
	}
	
	else{
	}

})

var full= firebase.database().ref().child("full");			//referring to firebase database child node(full)
full.on("value", function(datasnapshot){

	f = datasnapshot.val();	//get full value
	
	if(f == 1){
	dustbin_status.innerHTML = "100%";
	dustbin_status.style.color = "Red";
	alert("Dustbin is FULL!");
	
	var firebaseSendTime = firebase.database().ref().child("dustbin_history/" + "Full at " + time);
		firebaseSendTime.set("Full at " + time);
		
		setInterval(function(){ }, 10000);
	}
	
	else{
	}

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
