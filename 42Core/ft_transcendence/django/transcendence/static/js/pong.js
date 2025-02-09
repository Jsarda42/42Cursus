import { loadMultiPage } from "./loader.js";
import { loadPongIAPage } from "./loader.js";
import { loadPongLocalPage } from "./loader.js";
import { loadPongTournamentPage } from "./loader.js";
import { loadUltraPage} from "./loader.js";

let solo, multi, two_player, tournament, ia, mm1, mm2;

export function initPongGame() {
	solo = document.getElementById("solo-button");
	multi = document.getElementById("multi-button");
	two_player = document.getElementById("2p-button");
	tournament = document.getElementById("tournament-button");
	ia = document.getElementById("ia-button");
	mm1 = document.getElementById("1VS1");
	mm2 = document.getElementById("2VS2");

	function iabutton(){
		ia.addEventListener("click", function() {
			solo.style.display = "inline-block";
			multi.style.display = "inline-block";
			two_player.style.display = "none";
			tournament.style.display = "none";
			ia.style.display = "none";
			loadPongIAPage();
		})
	}
	function tournamentbutton(){
		tournament.addEventListener("click", function() {
			solo.style.display = "inline-block";
			multi.style.display = "inline-block";
			two_player.style.display = "none";
			tournament.style.display = "none";
			ia.style.display = "none";
			loadPongTournamentPage(); // tournament
			
		})
	}
	function two_playerbutton(){
		two_player.addEventListener("click", function() {
			solo.style.display = "inline-block";
			multi.style.display = "inline-block";
			two_player.style.display = "none";
			tournament.style.display = "none";
			ia.style.display = "none";
			loadPongLocalPage();
		})
	}
	function mm1button(){
		mm1.addEventListener("click", function(){
			solo.style.display = "inline-block";
			multi.style.display = "inline-block";
			mm1.style.display = "none";
			mm2.style.display = "none";
			loadMultiPage();
		})
	}

	function mm2button(){
		mm2.addEventListener("click", function(){
			solo.style.display = "inline-block";
			multi.style.display = "inline-block";
			mm1.style.display = "none";
			mm2.style.display = "none";
			loadUltraPage();
		})
	}
	function solobutton(){
		solo.addEventListener("click", function(){
			solo.style.display = "none";
			multi.style.display = "none";
			two_player.style.display = "inline-block";
			tournament.style.display = "inline-block";
			ia.style.display = "inline-block";
		});
	}
	function multibutton(){
		multi.addEventListener("click", function(){
			solo.style.display = "none";
			multi.style.display = "none";
			mm1.style.display = "inline-block";
			mm2.style.display = "inline-block";
		});
	}
	solobutton();
	multibutton();
	tournamentbutton();
	iabutton();
	two_playerbutton();
	mm1button();
	mm2button();
}


