import { initPongGame } from "./pong.js";

export var gameSocket;
export var runUltra = false;

export function falseRunUltra(){
    runUltra = false;
}

export function game_ultra(){
    // Global variables to manage the game state and controls
    var canvas, ctx, animationFrameId, P1, P2, P3, P4, user;
    var keyW = false; // Flag for key W press (left paddle movement)
    var keyS = false; // Flag for key S press (left paddle movement)
    var keyArrowUp = false; // Flag for ArrowUp key press (right paddle movement)
    var keyArrowDown = false; // Flag for ArrowDown key press (right paddle movement)
    var score1 = 0;  // Player 1's score
    var score2 = 0;  // Player 2's score

    // Get elements for the canvas and control buttons
    var canvas = document.getElementById("pong-canvas");
    var start = document.getElementById("start-button");
    var stop = document.getElementById("stop-button");

    // Ensure the canvas element exists
    if (!canvas) {
        console.error('Canvas element not found!');
    }

    // Set up the 2D drawing context
    ctx = canvas.getContext("2d");

    // Define the ball1 object
    var ball1 = {
        x: 0,
        y: 0,
        radius: 0,
        color: '#cc11f0',  // ball1 color
        draw: function () {
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, 2 * Math.PI, false);
            ctx.fillStyle = this.color;
            ctx.fill();
            ctx.lineWidth = this.radius / 2;
            ctx.strokeStyle = '#df73f4';
            ctx.stroke();
        }
    };
    // Define the ball2object
    var ball2 = {
        x: 0,
        y: 0,
        radius: 0,
        color: '#cc11f0',  // ball2 color
        draw: function () {
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, 2 * Math.PI, false);
            ctx.fillStyle = this.color;
            ctx.fill();
            ctx.lineWidth = this.radius / 2;
            ctx.strokeStyle = '#df73f4';
            ctx.stroke();
        }
    };
    var ball3 = {
        x: 0,
        y: 0,
        radius: 0,
        color: '#cc11f0',  // ball3 color
        draw: function () {
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, 2 * Math.PI, false);
            ctx.fillStyle = this.color;
            ctx.fill();
            ctx.lineWidth = this.radius / 2;
            ctx.strokeStyle = '#df73f4';
            ctx.stroke();
        }
    };

    var PTLP1 = {
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        color: '#05d9e8',
        onmovement: false, // Flag to check if the left paddle is moving
        draw: function () {
            // Draw the left paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        }
    };

    var PTLP2 = {
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        color: '#78006d',
        onmovement: false, // Flag to check if the left paddle is moving
        draw: function () {
            // Draw the left paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        }
    };

    var PBLP1 = {
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        color: '#05d9e8',
        onmovement: false, // Flag to check if the left paddle is moving
        draw: function () {
            // Draw the left paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        }
    };
    var PBLP2 = {
        x: 0,
        y: 0,
        width: 0,
        height: 0,
        color: '#78006d',
        onmovement: false, // Flag to check if the left paddle is moving
        draw: function () {
            // Draw the left paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        }
    };

    // Define the right paddle object
    var PTRP1 = {
        x: canvas.width,
        y: 0,
        width: 0,
        height: 0,
        color: '#d1d404',
        onmovement: false, // Flag to check if the right paddle is moving
        draw: function () {
            // Draw the right paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
    };
    var PTRP2 = {
        x: canvas.width,
        y: 0,
        width: 0,
        height: 0,
        color: '#d47004',
        onmovement: false, // Flag to check if the right paddle is moving
        draw: function () {
            // Draw the right paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
    };
    var PBRP1 = {
        x: canvas.width,
        y: 0,
        width: 0,
        height: 0,
        color: '#d1d404',
        onmovement: false, // Flag to check if LeftConnect True
        draw: function () {
            // Draw the right paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
    };
    var PBRP2 = {
        x: canvas.width,
        y: 0,
        width: 0,
        height: 0,
        color: '#d47004',
        onmovement: false, // Flag to check if the right paddle is moving
        draw: function () {
            // Draw the right paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
    };

    // Set canvas size based on its parent container's size
    setCanvasSize();
    function paddleDraw(){
        PBLP1.draw();
        PBRP1.draw();
        PBRP2.draw();
        PBLP2.draw();
        PTLP1.draw();
        PTLP2.draw();
        PTRP2.draw();
        PTRP1.draw();
    }

    // Main draw function to update the game state
    function draw() {
        if (!runUltra){
            gameClose();
            return 1;
        }
        clear();          // Clear the canvas
        drawLines();      // Draw the center line
        drawScore();      // Draw the score
        ball1.draw();      // Draw the ball1
        ball2.draw();
        ball3.draw();
        paddleDraw();
        animationFrameId = requestAnimationFrame(draw); // Request the next frame for animation
    }

    // Function to clear the canvas
    function clear() {
        ctx.fillStyle = "#005678"; // Background color
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }

    // Function to draw the center line
    function drawLines() {
        ctx.beginPath();
        ctx.moveTo(0, canvas.height / 2);
        ctx.lineTo(canvas.width, canvas.height / 2);
        ctx.moveTo(canvas.width / 2, 0);
        ctx.lineTo(canvas.width / 2, canvas.height);
        ctx.strokeStyle = '#c1c1c1'; // Line color
        ctx.stroke();
    }

    // Function to draw the score on the canvas
    function drawScore() {
        const fontsize = Math.min(canvas.width, canvas.height) * 0.25; // Dynamic font size
        ctx.fillStyle = '#d1f7ff';  // Score color
        ctx.font = fontsize + 'px Arial';

        // Calculate the positions for the score text
        const score1Width = ctx.measureText(score1).width;
        const score2Width = ctx.measureText(score2).width;
        const score1X = (canvas.width / 2 - canvas.width / 8) - (score1Width / 2);
        const score2X = (canvas.width / 2 + canvas.width / 8) - (score2Width / 2);
        const scoreY = canvas.height / 5 + fontsize / 4;

        // Draw the scores on the canvas
        ctx.fillText(score1, score1X, scoreY);
        ctx.fillText(score2, score2X, scoreY);
    }

    // Function to adjust the canvas size when the window is resized
    function setCanvasSize() {
        let width = document.getElementById("pong-canvas").parentElement.clientWidth;
        let height = width / 2;
        canvas.width = width;
        canvas.height = height;
    }

    // Function to update game state based on data from the server
    function updateVals(data){
        var objects = JSON.parse(data.message); // Parse game data

        var positions = objects.filter(item => item.position).map(item => item.position);
        var width = objects.filter(item => item.width).map(item => item.width);
        var height = objects.filter(item => item.height).map(item => item.height);
        var radius = objects.filter(item => item.radius).map(item => item.radius);
        var score = objects.filter(item => item.score).map(item => item.score);

        // SCORE
        score1 = score[0][0];
        score2 = score[0][1];
        //ball1
        ball1.x = positions[0][0] * canvas.width;
        ball1.y = positions[0][1] * canvas.height;
        ball1.radius = radius[0] * Math.min(canvas.width/2, canvas.height/2);
        //ball2
        ball2.x = positions[1][0] * canvas.width;
        ball2.y = positions[1][1] * canvas.height;
        ball2.radius = radius[1] * Math.min(canvas.width/2, canvas.height/2);
        //ball3
        ball3.x = positions[2][0] * canvas.width;
        ball3.y = positions[2][1] * canvas.height;
        ball3.radius = radius[2] * Math.min(canvas.width/2, canvas.height/2);
        //P1LEFT
        PTLP1.x = positions[3][0] * canvas.width;
        PTLP1.y = positions[3][1] * canvas.height;
        PTLP1.width = width[0] * canvas.width;
        PTLP1.height = height[0] * canvas.height;
        PBLP1.x = positions[4][0] * canvas.width;
        PBLP1.y = positions[4][1] * canvas.height;
        PBLP1.width = width[1] * canvas.width;
        PBLP1.height = height[1] * canvas.height;
        //P2LEFT
        PTLP2.x = positions[5][0] * canvas.width;
        PTLP2.y = positions[5][1] * canvas.height;
        PTLP2.width = width[2] * canvas.width;
        PTLP2.height = height[2] * canvas.height;
        PBLP2.x = positions[6][0] * canvas.width;
        PBLP2.y = positions[6][1] * canvas.height;
        PBLP2.width = width[3] * canvas.width;
        PBLP2.height = height[3] * canvas.height;
        //P1RIGHT
        PTRP1.x = positions[7][0] * canvas.width;
        PTRP1.y = positions[7][1] * canvas.height;
        PTRP1.width = width[4] * canvas.width;
        PTRP1.height = height[4] * canvas.height;
        PBRP1.x = positions[8][0] * canvas.width;
        PBRP1.y = positions[8][1] * canvas.height;
        PBRP1.width = width[5] * canvas.width;
        PBRP1.height = height[5] * canvas.height;
        //P2RIGHT
        PTRP2.x = positions[9][0] * canvas.width;
        PTRP2.y = positions[9][1] * canvas.height;
        PTRP2.width = width[6] * canvas.width;
        PTRP2.height = height[6] * canvas.height;
        PBRP2.x = positions[10][0] * canvas.width;
        PBRP2.y = positions[10][1] * canvas.height;
        PBRP2.width = width[7] * canvas.width;
        PBRP2.height = height[7] * canvas.height;
    }
    function KeyDown(e) {
        // Set the flags when keys are pressed
        if (!keyArrowUp && e.key === 'ArrowUp' || !keyArrowDown && e.key === 'ArrowDown')
        {
            if (e.key === 'ArrowUp') keyArrowUp = true;
            if (e.key === 'ArrowDown') keyArrowDown = true;
            updatemovementsArrow();
        }
        if (!keyW && e.key === 'w' || !keyW && e.key === 's')
        {
            if (e.key === 'w') keyW = true;
            if (e.key === 's') keyS = true;
            updatemovementsWS();
        }
    };

    function KeyUp(e) {
        // Reset the paddle movement flags when keys are released
        if (e.key === 'ArrowUp' || e.key === 'ArrowDown'){
            if (e.key === 'ArrowUp') keyArrowUp = false;
            if (e.key === 'ArrowDown') keyArrowDown = false;
            updatemovementsArrow();
        }
        if (e.key === 'w' || e.key === 's'){
            if (e.key === 'w') keyW = false;
            if (e.key === 's') keyS = false;
            updatemovementsWS();
        }
    };


    // Function to initialize the game when it starts
    function onGameStart(){
        window.addEventListener("keyup", KeyUp);
        window.addEventListener("keydown", KeyDown);
        // Start the game loop
        draw();
    }

    function gameClose(){
        ctx.fillStyle = "#005678";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        score1 = 0;
        score2 = 0;
        ball1.x = canvas.width / 2;
        ball1.y = canvas.height / 2;
        ball2.x = canvas.width / 2;
        ball2.y = canvas.height / 2;
        ball3.x = canvas.width / 2;
        ball3.y = canvas.height / 2;
        canvas.style.display = "none";
        start.style.display = "inline-block";
        stop.style.display = "none";
        window.removeEventListener("keyup", KeyUp);
        window.removeEventListener("keydown", KeyDown);
        // start.removeEventListener("click", startClickHandler);
        gameSocket.send(JSON.stringify({
            'message' : 'stop'
        }));
        runUltra = false;
        cancelAnimationFrame(animationFrameId);
        FetchPongHTML();
        return 1;
    }

    stop.addEventListener("click", gameClose);

    function updatemovementsArrow(){
        let message;
        if (keyArrowUp && keyArrowDown || !keyArrowUp && !keyArrowDown) {
            message = "false";
            gameSocket.send(JSON.stringify({
            'message': message
            }));
        }
        else if (keyArrowUp && !keyArrowDown) {
            message = "up";
            gameSocket.send(JSON.stringify({
                'message': message
            }));
        }
        else if (keyArrowDown && !keyArrowUp) {
            message = "down";
            gameSocket.send(JSON.stringify({
                'message': message
            }));
        }
    }

    function updatemovementsWS(){
        let message;
        if (keyW && keyS || !keyW && !keyS) {
            message = "falseWS";
            gameSocket.send(JSON.stringify({
            'message': message
            }));
        }
        else if (keyW && !keyS) {
            message = "W";
            gameSocket.send(JSON.stringify({
                'message': message
            }));
        }
        else if (keyS && !keyW) {
            message = "S";
            gameSocket.send(JSON.stringify({
                'message': message
            }));
        }
    }
    function OnGameWait(){
        clear();
        var color;
        var toprint = "Your color is :";
        const fontsize = Math.min(canvas.width, canvas.height) * 0.25; // Dynamic font size
        ctx.fillStyle = '#d1f7ff';
        ctx.font = fontsize + 'px Arial';
        var toprintWidth = ctx.measureText(toprint).width;
        var toprintX = (canvas.width / 2) - (toprintWidth / 2);
        var toprintY = canvas.height / 2 + fontsize / 4;
        ctx.fillText(toprint, toprintX, toprintY);
        if (user === P1){
            color = PTLP1.color;
            //console.log("bleu");
        }
        if (user === P2){
            color = PBLP2.color;
            //console.log("violet");
        }
        if (user === P3){
            color = PTRP1.color
            //console.log("jaune")
        }
        if (user === P4){
            color = PBRP2.color
            //console.log("orange");
        }
        ctx.beginPath();
        ctx.arc(canvas.width / 2, canvas.height/2 + canvas.height/4, 0.03*canvas.width, 0, 2 * Math.PI, false);
        ctx.fillStyle = color;
        ctx.fill();
        ctx.stroke();
    }

    function startClickHandler() {
        start.style.display = "none";
        stop.style.display = "inline-block";
        canvas.style.display = "inline-block";
        //console.log(gameSocket);
        gameSocket = new WebSocket('wss://' + window.location.host + '/ws/game_four/');
        //console.log("new websocket")
        //console.log(gameSocket);
        gameSocket.onclose = function(e) {
            console.error('socket closed unexpectedly');
        };
        gameSocket.onmessage = function(e){ 
            var data = JSON.parse(e.data);
            if (data.type === 'game_state' && data.message) {
                updateVals(data);
            }
            if (data.event === "game_start") {
                //console.log("Game start")
                runUltra = true;
                onGameStart();
            }
            if (data.event === "game_wait"){
                var data = JSON.parse(e.data);
                P1 = data.left_player;
                P2 = data.second_leftplayer;
                P3 = data.right_player;
                P4 = data.second_rightplayer;
                user = data.user;
                //console.log(P1,P2,P3,P4, user);
                //console.log("Game wait");
                OnGameWait();
            }
        };
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

    start.removeEventListener("click", startClickHandler);

    start.addEventListener("click", startClickHandler);

    window.addEventListener("resize", setCanvasSize);

}