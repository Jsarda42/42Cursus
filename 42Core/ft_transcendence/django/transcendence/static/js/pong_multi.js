import { initPongGame } from "./pong.js";

export var gameSocket;
export var runMulti = false;

export function falseRunMulti(){
    runMulti = false;
}

export function game_multi(){
    // Global variables to manage the game state and controls
    var canvas, ctx, animationFrameId;
    var keyW = false; // Flag for key W press (left paddle movement)
    var keyS = false; // Flag for key S press (left paddle movement)
    var keyArrowUp = false; // Flag for ArrowUp key press (right paddle movement)
    var keyArrowDown = false; // Flag for ArrowDown key press (right paddle movement)
    var score1 = 0;  // Player 1's score
    var score2 = 0;  // Player 2's score
    var P1;
    var P2;
    var user;

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

    // Define the ball object
    var ball = {
        x: 0,
        y: 0,
        radius: 0,
        color: '#cc11f0',  // Ball color
        draw: function () {
            // Draw the ball on the canvas
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, 2 * Math.PI, false);
            ctx.fillStyle = this.color;
            ctx.fill();
            ctx.lineWidth = this.radius / 2;
            ctx.strokeStyle = '#df73f4';
            ctx.stroke();
        }
    };

    // Define the left paddle object
    var paddleLeft = {
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

    // Define the right paddle object
    var paddleRight = {
        x: canvas.width,
        y: 0,
        width: 0,
        height: 0,
        color: '#78006d',
        onmovement: false, // Flag to check if the right paddle is moving
        draw: function () {
            // Draw the right paddle on the canvas
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
    };

    // Set canvas size based on its parent container's size
    setCanvasSize();

    // Main draw function to update the game state
    function draw() {
        if (!runMulti){
            gameClose();
            return 1;
        }
        if (score1 === 3 || score2 === 3)
        {
            displayWin()
            return 1;
        }
        clear();          // Clear the canvas
        drawLines();      // Draw the center line
        drawScore();      // Draw the score
        ball.draw();      // Draw the ball
        paddleLeft.draw(); // Draw the left paddle
        paddleRight.draw(); // Draw the right paddle
        animationFrameId = requestAnimationFrame(draw); // Request the next frame for animation
    }

    function displayWin(){
        clear();
        var toprint;
        if (score1 === 3)
            toprint = P1 + " WIN";
        else
            toprint = P2 + " WIN";
        var fontsize = Math.min(canvas.width, canvas.height) * 0.25; // Dynamic font size
        ctx.fillStyle = '#d1f7ff';  // Score color
        ctx.font = fontsize + 'px Arial';
        var toprintWidth = ctx.measureText(toprint).width;
        while (toprintWidth > canvas.width * 0.9) {
            fontsize *= 0.9;
            ctx.font = fontsize + 'px Arial';
            toprintWidth = ctx.measureText(toprint).width;
        }
        var toprintX = (canvas.width / 2) - (toprintWidth / 2);
        var toprintY = canvas.height / 2 + fontsize / 4;
        ctx.fillText(toprint, toprintX, toprintY);
    }

    // Function to clear the canvas
    function clear() {
        ctx.fillStyle = "#005678"; // Background color
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }

    // Function to draw the center line
    function drawLines() {
        ctx.beginPath();
        ctx.moveTo(canvas.width / 2, 0);
        ctx.lineTo(canvas.width / 2, canvas.height);
        ctx.strokeStyle = '#d1f7ff'; // Line color
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
        const score1X = (canvas.width / 4) - (score1Width / 2);
        const score2X = (canvas.width * 3 / 4) - (score2Width / 2);
        const scoreY = canvas.height / 2 + fontsize / 4;

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

        // Update the game state with the new values
        score1 = score[0][0];
        score2 = score[0][1];
        ball.x = positions[0][0] * canvas.width;
        ball.y = positions[0][1] * canvas.height;
        ball.radius = radius * Math.min(canvas.width/2, canvas.height/2);
        paddleLeft.y = positions[1][1] * canvas.height;
        paddleLeft.width = width[0] * canvas.width;
        paddleLeft.height = height[0] * canvas.height;
        paddleRight.y = positions[2][1] * canvas.height;
        paddleRight.width = width[1] * canvas.width;
        paddleRight.x = canvas.width - paddleRight.width;
        paddleRight.height = height[1] * canvas.height;
    }
    function KeyDown(e) {
        // Set the flags when keys are pressed
        if (!keyArrowUp && e.key === 'ArrowUp' || !keyArrowDown && e.key === 'ArrowDown')
        {
            if (e.key === 'ArrowUp') keyArrowUp = true;
            if (e.key === 'ArrowDown') keyArrowDown = true;
            updatemovements();
        }
    };

    function KeyUp(e) {
        // Reset the paddle movement flags when keys are released
        if (e.key === 'ArrowUp') keyArrowUp = false;
        if (e.key === 'ArrowDown') keyArrowDown = false;
        updatemovements();
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
        ball.x = canvas.width / 2;
        ball.y = canvas.height / 2;
        canvas.style.display = "none";
        start.style.display = "inline-block";
        stop.style.display = "none";
        window.removeEventListener("keyup", KeyUp);
        window.removeEventListener("keydown", KeyDown);
        // start.removeEventListener("click", startClickHandler);
        gameSocket.send(JSON.stringify({
            'message' : 'stop'
        }));
        runMulti = false;
        cancelAnimationFrame(animationFrameId);
        FetchPongHTML();
        return 1;
    }

    
    function updatemovements(){
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
    
    function OnGameWait(){
        clear();
        var color;
        var toprint = "Your color is :";
        const fontsize = Math.min(canvas.width, canvas.height) * 0.25; // Dynamic font size
        ctx.fillStyle = '#d1f7ff';  // Score color
        ctx.font = fontsize + 'px Arial';
        var toprintWidth = ctx.measureText(toprint).width;
        var toprintX = (canvas.width / 2) - (toprintWidth / 2);
        var toprintY = canvas.height / 2 + fontsize / 4;
        ctx.fillText(toprint, toprintX, toprintY);
        if (user === P1)
            color = paddleLeft.color;
        if (user === P2)
            color = paddleRight.color;
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
        gameSocket = new WebSocket('wss://' + window.location.host + '/ws/game/');
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
                runMulti = true;
                onGameStart();
            }
            if (data.event === "game_wait"){
                var data = JSON.parse(e.data);
                P1 = data.left_player;
                P2 = data.right_player;
                user = data.user;
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
    
    stop.addEventListener("click", gameClose);
}