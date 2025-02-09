var canvas, ctx, animationFrameId, start, stop, pause;

import { displayError } from "./display_message.js";
import { initPongGame } from "./pong.js";

export var runTournament = false;
export function falserunTournament(){
    runTournament = false;
}

export function tournament() {
    document.getElementById("start-tournament-btn").addEventListener("click", openPlayerForm);

    let players = [];
    let winners = [];
    let finalMatch = [];
    let finalWinner = "";
    let currentMatch = [];
    let ongoingGame = false;

    function openPlayerForm() {
        document.getElementById("player-form-container").style.display = "block";
        document.getElementById("start-tournament-btn").style.display = "none";
    }

    document.getElementById("submit-players").addEventListener("click", function () {
        players = [];
        for (let i = 1; i <= 4; i++) {
            let playerName = document.getElementById(`player${i}`).value.trim();
            if (playerName) {
                playerName = sanitizeInput(playerName);
                players.push(playerName);
            }
        }

        if (players.length === 4) {
            document.getElementById("player-form-container").style.display = "none";
            startTournament();
        } else {
            displayError("You need exactly 4 players to start the tournament.");
        }
    });

    function sanitizeInput(input) {
        
        const element = document.createElement('div');
        element.innerText = input;
        return element.innerHTML;
    }
    function startTournament() {
        //console.log("Tournament Starting with Players:", players);
        winners = [];
        document.getElementById("game-container").style.display = "block";
        playMatch(players[0], players[1]);
    }

    function playMatch(player1, player2) {
        if (ongoingGame) return;
        ongoingGame = true;
        currentMatch = [player1, player2];
    
        document.getElementById("match-info").innerText = `Match to play is: ${player1} vs ${player2}`;
    
        //console.log("Game Starting for", player1, "vs", player2);
    
        // Start the game directly
        game_tournament(player1, player2, function (winner) {
            //console.log("Match Winner:", winner);
            winners.push(winner);
            ongoingGame = false;
            document.getElementById("start-button").style.display = "inline-block";
            nextRound();
        });
    }

    function nextRound() {
        if (winners.length === 2) {
            // Move to Final
            //console.log("Moving to the final match:", winners);
            finalMatch = [...winners];
            winners = [];
            playMatch(finalMatch[0], finalMatch[1]);
        } else if (winners.length === 1 && finalMatch.length === 2) {
            
            finalWinner = winners[0];
            //console.log("Final Winner:", finalWinner);
            document.getElementById("match-info").innerText = `🏆 Champion: ${finalWinner}!`;
        } else {
            //console.log("moving to the 2nd match")
            //console.log(winners)
            playMatch(players[2], players[3]);
            
        }
    }
}

function game_tournament(player1, player2, onWinCallback){
    var keyW = false;
    var keyS = false;
    var keyArrowUp = false;
    var keyArrowDown = false;
    var score1 = 0;
    var score2 = 0;
    var winningScore = 3;

    canvas = document.getElementById("pong-canvas");
    start = document.getElementById("start-button");
    stop = document.getElementById("stop-button");
    if (!canvas) {
        console.error('Canvas element not found!');
    }
    ctx = canvas.getContext("2d");

    var ball = {
        x: canvas.width / 2,
        y: canvas.height / 2,
        vx: 2,
        vy: 0,
        speed: 1.5,
        radius: Math.min(canvas.width/2, canvas.height/2) * 0.03,
        color: '#cc11f0',
        draw: function () {
            if (this.y + this.radius/2 + this.vy > canvas.height || this.y + this.vy < 0) {
                this.vy = -this.vy;
            }
            if (this.x + this.radius/2 + this.vx > paddleRight.x && this.y > paddleRight.y && this.y < paddleRight.y + paddleRight.height){
                checkCollisionRight();
            }
            if (this.x + this.vx < paddleLeft.x + paddleLeft.width && this.y > paddleLeft.y && this.y < paddleLeft.y + paddleLeft.height){
                checkCollisionLeft();
            }
            if (this.x + this.vx > canvas.width - paddleLeft.width / 2) {
                ball.x = canvas.width / 2;
                ball.y = canvas.height / 2;
                ball.speed = 1.5;
                ball.vx = 2;
                ball.vy = 0;
                score1++;
            }
            if (this.x + this.vx < 0 + paddleLeft.width / 2) {
                ball.x = canvas.width / 2;
                ball.y = canvas.height / 2;
                ball.speed = 1.5;
                ball.vx = -2;
                ball.vy = 0;
                score2++;
            }
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, 2 * Math.PI, false);
            ctx.fillStyle = this.color;
            ctx.fill();
            ctx.lineWidth = this.radius / 2;
            ctx.strokeStyle = '#df73f4';
            ctx.stroke();
        },
        move: function () {
            this.x += this.vx * this.speed;
            this.y += this.vy * this.speed;
        }
    };

    var paddleLeft = {
        x: 0,
        y: canvas.height / 2 - canvas.height / 8,
        width: canvas.width / 80,
        height: canvas.height / 6,
        color: '#05d9e8',
        onmovement: false,
        draw: function () {
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
        move: function (){
            const speed = 7.5;
            if (this.onmovement === "up" && this.y > 0) {
                this.y -= speed;
            }
            if (this.onmovement === "down" && this.y + this.height < canvas.height) {
                this.y += speed;
            }
        }
    };

    var paddleRight = {
        x: canvas.width,
        y: canvas.height / 2 - canvas.height / 8,
        width: canvas.width / 80,
        height: canvas.height / 6,
        color: '#05d9e8',
        onmovement: false,
        draw: function () {
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
        move: function (){
            const speed = 7.5;
            if (this.onmovement === "up" && this.y > 0) {
                this.y -= speed;
            }
            if (this.onmovement === "down" && this.y + this.height < canvas.height) {
                this.y += speed;
            }
        }
    };

    setCanvasSize();

    function checkCollisionRight(){
        let relativeImpact = (ball.y - (paddleRight.y + paddleRight.height / 2)) / (paddleRight.height / 2);
        let maxAngle = Math.PI / 4;
        let angle = relativeImpact * maxAngle;
        ball.vy = ball.speed * Math.sin(angle);
        ball.vx = -ball.speed * Math.cos(angle);
        if (ball.speed < 4){
            ball.speed *= 1.1;
        }
    }

    function checkCollisionLeft(){
        let relativeImpact = (ball.y - (paddleLeft.y + paddleLeft.height / 2)) / (paddleLeft.height / 2);
        let maxAngle = Math.PI / 4;
        let angle = relativeImpact * maxAngle;
        ball.vy = ball.speed * Math.sin(angle);
        ball.vx = ball.speed * Math.cos(angle);
        if (ball.speed < 4){
            ball.speed *= 1.1;
        }
    }

    window.addEventListener("keyup", function (e) {
        if (e.key === 'w')
            keyW = false;
        if (e.key === 's')
            keyS = false;
        if (e.key === 'ArrowUp')
            keyArrowUp = false;
        if (e.key === 'ArrowDown')
            keyArrowDown = false;
        updatemovements();
    });
    
    window.addEventListener("keydown", function (e) {
        if (e.key === 'w')
            keyW = true;
        if (e.key === 's')
            keyS = true;
        if (e.key === 'ArrowUp')
            keyArrowUp = true;
        if (e.key === 'ArrowDown')
            keyArrowDown = true;
        updatemovements();
    });
    
    function updatemovements(){
        if (keyW && !keyS) {
            paddleLeft.onmovement = "up";
        }
        if (keyS && !keyW) {
            paddleLeft.onmovement = "down";
        }
        if (keyArrowUp && !keyArrowDown) {
            paddleRight.onmovement = "up";
        }
        if (keyArrowDown && !keyArrowUp) {
            paddleRight.onmovement = "down";
        }
        if (keyS && keyW || !keyS && !keyW) {
            paddleLeft.onmovement = false;
        }
        if (keyArrowUp && keyArrowDown || !keyArrowUp && !keyArrowDown) {
            paddleRight.onmovement = false;
        }
    }
    
    function draw() {
        if (!runTournament){
            endGame();
            return 1;
        }
        if (score1 >= winningScore) {
            endmatch();
            onWinCallback(player1);
            return;  
        }
        if (score2 >= winningScore) {
            endmatch();
            onWinCallback(player2);
            return; 
        }
        clear();
        drawLines();
        drawScore();
        ball.move();
        paddleLeft.move();
        paddleRight.move();
        ball.draw();
        paddleLeft.draw();
        paddleRight.draw();
        animationFrameId = requestAnimationFrame(draw);
        runTournament=true;
    }

    function clear() {
        ctx.fillStyle = "#005678";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }
    
    function drawLines() {
        ctx.beginPath();
        ctx.moveTo(canvas.width / 2, 0);
        ctx.lineTo(canvas.width / 2, canvas.height);
        ctx.strokeStyle = '#d1f7ff';
        ctx.stroke();
    }

    function drawScore() {
        const fontsize = Math.min(canvas.width, canvas.height) * 0.25;
        ctx.fillStyle = '#d1f7ff';
        ctx.font = fontsize + 'px Arial';

        const score1Width = ctx.measureText(score1).width;
        const score2Width = ctx.measureText(score2).width;

        const score1X = (canvas.width / 4) - (score1Width / 2);
        const score2X = (canvas.width * 3 / 4) - (score2Width / 2);

        const scoreY = canvas.height / 2 + fontsize / 4;

        ctx.fillText(score1, score1X, scoreY);
        ctx.fillText(score2, score2X, scoreY);
    }

    function initYvals(){
            paddleLeft.y = canvas.height / 2 - canvas.height / 8;
            paddleRight.y = canvas.height / 2 - canvas.height / 8;
            ball.y = canvas.height / 2;
            ball.x = canvas.width / 2;
    }
    function setCanvasSize() {
    
        let width = document.getElementById("pong-canvas").parentElement.clientWidth;
        let height = width / 2;
        canvas.width = width;
        canvas.height = height;
        ball.radius = Math.min(canvas.width/2, canvas.height/2) * 0.03,
        paddleLeft.width = canvas.width / 80;
        paddleLeft.height = canvas.height / 6;
        paddleRight.width = canvas.width / 80;
        paddleRight.height = canvas.height / 6;
        paddleRight.x = canvas.width - paddleRight.width;
    }
    function endGame(){
        //console.log("endGame");
        if (runTournament == true){
            cancelAnimationFrame(animationFrameId);
            runTournament = false;
        }
        ctx.fillStyle = "#005678";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        score1 = 0;
        score2 = 0;
        ball.x = canvas.width / 2;
        ball.y = canvas.height / 2;
        ball.speed = 1.5;
        ball.vx = 2;
        ball.vy = 0;
        score1 = 0;
        score2 = 0;
        canvas.style.display = "none";
        stop.style.display = "none";
        start.style.display = "inline-block";
        FetchPongHTML();
        return 1;
    }

    function endmatch(){
        //console.log("endmatch");
        if (runTournament == true){
            cancelAnimationFrame(animationFrameId);
            runTournament = false;
        }
        ctx.fillStyle = "#005678";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        score1 = 0;
        score2 = 0;
        ball.x = canvas.width / 2;
        ball.y = canvas.height / 2;
        ball.speed = 1.5;
        ball.vx = 2;
        ball.vy = 0;
        score1 = 0;
        score2 = 0;
        canvas.style.display = "none";
        stop.style.display = "none";
        start.style.display = "inline-block";
        start.removeEventListener("click", startGame);
        return 1;
    }
    
    start.addEventListener("click", startGame);
    
    function startGame() {
        start.style.display = "none";
        stop.style.display = "inline-block";
        initYvals();
        canvas.style.display = "inline-block";
        runTournament = true;
        draw();
    }
        stop.addEventListener("click", endGame);
}

function FetchPongHTML(){
    const mainContent = document.getElementById("main-content");
    fetch("/static/pong.html")
        .then(response => response.text())
        .then(data => {
            mainContent.innerHTML = data;

            if (!document.querySelector('script[src="/static/js/pong.js"]')) {
                let script = document.createElement('script');
                script.src = '/static/js/pong.js';
                script.type = 'module';
                script.onload = function () {
                    //console.log('Pong game script loaded');
                    initPongGame();
                };
                document.body.appendChild(script);
            } else {
                initPongGame();
            }
        })
        .catch(error => console.error("Error loading Pong game:", error));
    }

// function game_tournament_mode(player1, player2, onWinCallback) {
//     var canvas = document.getElementById("pong-canvas");
//     var ctx = canvas.getContext("2d");

//     var score1 = 0;
//     var score2 = 0;
//     var winningScore = 3;

//     var ball = { x: canvas.width / 2, y: canvas.height / 2, vx: 2, vy: 0, speed: 2.5 };
//     var paddleLeft = { x: 0, y: canvas.height / 2 - 40, width: 10, height: 80, onmovement: false };
//     var paddleRight = { x: canvas.width - 10, y: canvas.height / 2 - 40, width: 10, height: 80, onmovement: false };

//     var keyW = false, keyS = false, keyArrowUp = false, keyArrowDown = false;

    
//     window.addEventListener("keydown", function (e) {
//         if (e.key === 'w') keyW = true;
//         if (e.key === 's') keyS = true;
//         if (e.key === 'ArrowUp') keyArrowUp = true;
//         if (e.key === 'ArrowDown') keyArrowDown = true;
//     });

//     window.addEventListener("keyup", function (e) {
//         if (e.key === 'w') keyW = false;
//         if (e.key === 's') keyS = false;
//         if (e.key === 'ArrowUp') keyArrowUp = false;
//         if (e.key === 'ArrowDown') keyArrowDown = false;
//     });

//     function updatePlayerMovement() {
//         const paddleSpeed = 7.5;

       
//         if (keyW && paddleLeft.y > 0) paddleLeft.y -= paddleSpeed;
//         if (keyS && paddleLeft.y + paddleLeft.height < canvas.height) paddleLeft.y += paddleSpeed;

   
//         if (keyArrowUp && paddleRight.y > 0) paddleRight.y -= paddleSpeed;
//         if (keyArrowDown && paddleRight.y + paddleRight.height < canvas.height) paddleRight.y += paddleSpeed;
//     }

//     function updateGame() {
//         ball.x += ball.vx * ball.speed;
//         ball.y += ball.vy * ball.speed;

//         if (ball.y <= 0 || ball.y >= canvas.height) ball.vy *= -1;

        
//         if (ball.x <= paddleLeft.x + paddleLeft.width && ball.y > paddleLeft.y && ball.y < paddleLeft.y + paddleLeft.height) {
//             ball.vx *= -1;
//         }

//         if (ball.x >= paddleRight.x - paddleRight.width && ball.y > paddleRight.y && ball.y < paddleRight.y + paddleRight.height) {
//             ball.vx *= -1;
//         }

       
//         if (ball.x < 0) {
//             score2++;
//             resetBall();
//         }
//         if (ball.x > canvas.width) {
//             score1++;
//             resetBall();
//         }

       


      
//         updatePlayerMovement();
//         drawGame();
//         requestAnimationFrame(updateGame);
//     }

//     function resetBall() {
//         ball.x = canvas.width / 2;
//         ball.y = canvas.height / 2;
//         ball.vx = 2 * (Math.random() > 0.5 ? 1 : -1);
//         ball.vy = 2 * (Math.random() > 0.5 ? 1 : -1);
//     }

//     function drawGame() {
//         ctx.clearRect(0, 0, canvas.width, canvas.height);
//         ctx.fillStyle = "white";
//         ctx.fillRect(paddleLeft.x, paddleLeft.y, paddleLeft.width, paddleLeft.height);
//         ctx.fillRect(paddleRight.x, paddleRight.y, paddleRight.width, paddleRight.height);
//         ctx.beginPath();
//         ctx.arc(ball.x, ball.y, 5, 0, Math.PI * 2);
//         ctx.fill();
//         ctx.font = "20px Arial";
//         ctx.fillText(`${player1}: ${score1}`, 20, 30);
//         ctx.fillText(`${player2}: ${score2}`, canvas.width - 100, 30);
//     }

   
//     var startButton = document.getElementById("start-button");
//     var gameContainer = document.getElementById("game-container");
    
   
//         startButton.addEventListener("click", function startGame() {
//         gameContainer.style.display = "block";
//         startButton.style.display = "none";
    
//         resetBall();
//         updateGame();
    
       
//         startButton.removeEventListener("click", startGame);
//     });
    
//     function setCanvasSize() {
//         let width = window.innerWidth * 0.8; 
//         let height = window.innerHeight * 0.6;
//         canvas.width = width;
//         canvas.height = height;
//         ball.radius = Math.min(canvas.width / 2, canvas.height / 2) * 0.03;
//         paddleLeft.width = canvas.width / 80;
//         paddleLeft.height = canvas.height / 6;
//         paddleRight.width = canvas.width / 80;
//         paddleRight.height = canvas.height / 6;
//         paddleRight.x = canvas.width - paddleRight.width;
//     }

//     window.addEventListener("resize", setCanvasSize);
//     setCanvasSize(); 

    
//     resetBall();
// }