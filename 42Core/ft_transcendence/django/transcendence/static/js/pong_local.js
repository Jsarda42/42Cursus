import { initPongGame } from "./pong.js";

export var runLocal = false;
export function falseRunLocal(){
    runLocal = false;
}
export function game_local(){
    var canvas, ctx, animationFrameId, start, stop, pause;
    var keyW = false;
    var keyS = false;
    var keyArrowUp = false;
    var keyArrowDown = false;
    var score1 = 0;
    var score2 = 0;

    canvas = document.getElementById("pong-canvas");
    start = document.getElementById("start-button");
    stop = document.getElementById("stop-button");
    pause = document.getElementById("pause-button");

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
        //console.log(animationFrameId);
        if (!runLocal)
            return 1;
        if (score1 === 3 || score2 === 3)
        {
            displayWin()
            return 1;
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
        runLocal=true;
    }

    function clear() {
        ctx.fillStyle = "#005678";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    }

    function displayWin(){
        clear();
        pause.style.display = "none";
        var toprint;
        if (score1 === 3)
            toprint = "P1 WIN";
        else
            toprint = "P2 WIN";
        const fontsize = Math.min(canvas.width, canvas.height) * 0.25; // Dynamic font size
        ctx.fillStyle = '#d1f7ff';  // Score color
        ctx.font = fontsize + 'px Arial';
        var toprintWidth = ctx.measureText(toprint).width;
        var toprintX = (canvas.width / 2) - (toprintWidth / 2);
        var toprintY = canvas.height / 2 + fontsize / 4;
        ctx.fillText(toprint, toprintX, toprintY);
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

    function initYvals(){
        paddleLeft.y = canvas.height / 2 - canvas.height / 8;
        paddleRight.y = canvas.height / 2 - canvas.height / 8;
        ball.y = canvas.height / 2;
        ball.x = canvas.width / 2;
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

    start.addEventListener("click", function(){
        start.style.display = "none";
        pause.style.display = "inline-block";
        stop.style.display = "inline-block";
        initYvals();
        canvas.style.display = "inline-block";
        runLocal = true;
        draw();
    });

    stop.addEventListener("click", function(){
        if (runLocal == true){
            cancelAnimationFrame(animationFrameId);
            runLocal = false;
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
        canvas.style.display = "none";
        stop.style.display = "none";
        pause.style.display = "none";
        start.style.display = "inline-block";
        FetchPongHTML();
        return 1;
    });

    pause.addEventListener("click", function(){
        if (runLocal == true){
            cancelAnimationFrame(animationFrameId);
            runLocal=false;
        }
        else {
            animationFrameId = requestAnimationFrame(draw);
            runLocal=true;
        }
    });

    window.addEventListener("resize", setCanvasSize);
}