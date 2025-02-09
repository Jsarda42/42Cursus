import { initPongGame } from "./pong.js";

export var runIA = false;

export function falseRunIA(){
    runIA = false;
}
export function game_ia(){
    var canvas, ctx, animationFrameId, errorMargin, scaleFactor, start, stop;
    var keyW = false;
    var keyS = false;
    var keyArrowUp = false;
    var keyArrowDown = false;
    var score1 = 0;
    var score2 = 0;
    var slider = document.getElementById('slider');
    var thumb = document.getElementById('thumb');
    var valueDisplay = document.getElementById('value');
    var sliderWidth = slider.offsetWidth;
    var positions = [0, sliderWidth / 2, sliderWidth]; // Positions pour les valeurs 1, 2, 3
    var difficulty = 2; // Valeur initiale
    
    function setThumbPosition(x) {
      const sliderRect = slider.getBoundingClientRect();
      let relativeX = x - sliderRect.left;
    
      // Contrainte dans la barre
      relativeX = Math.max(0, Math.min(relativeX, sliderWidth));
    
      // Trouver la position la plus proche
      const closestPosition = positions.reduce((prev, curr) => 
        Math.abs(curr - relativeX) < Math.abs(prev - relativeX) ? curr : prev
      );
    
      // Déplacer le rond (thumb)
      thumb.style.left = `${closestPosition}px`;
    
      // Définir la valeur
      difficulty = positions.indexOf(closestPosition) + 1;
    }
    
    // Événements pour déplacer le rond
    thumb.addEventListener('mousedown', () => {
      document.addEventListener('mousemove', onDrag);
      document.addEventListener('mouseup', stopDrag);
    });
    
    function onDrag(e) {
      setThumbPosition(e.clientX);
    }
    
    function stopDrag() {
      document.removeEventListener('mousemove', onDrag);
      document.removeEventListener('mouseup', stopDrag);
    }
    
    
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
        futureY: canvas.height / 2, 
        color: '#cc11f0',
        draw: function () {
            if (this.y + this.radius + this.vy > canvas.height) {
                this.y = canvas.height - this.radius;
                this.vy = -this.vy;
            }
            if (this.y - this.radius + this.vy < 0) {
                this.y = this.radius;
                this.vy = -this.vy;
            }
            if (this.y + this.radius/2 + this.vy > canvas.height || this.y + this.vy < 0) {
                this.vy = -this.vy;
            }
            if (this.x + this.radius + this.vx > paddleRight.x) {
                if (this.y + this.radius >= paddleRight.y && this.y - this.radius <= paddleRight.y + paddleRight.height) {
                    checkCollisionRight();
                }
            }
            
            if (this.x - this.radius + this.vx < paddleLeft.x + paddleLeft.width) {
                if (this.y + this.radius >= paddleLeft.y && this.y - this.radius <= paddleLeft.y + paddleLeft.height) {
                    checkCollisionLeft();
                }
            }
            if (this.x + this.radius > canvas.width && this.x + this.radius + this.vx > canvas.width) {
                resetBall(1);
            }
            if (this.x - this.radius < 0 && this.x - this.radius + this.vx < 0) {
                resetBall(2);
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
            this.x += this.vx * this.speed * scaleFactor;
            this.y += this.vy * this.speed * scaleFactor;
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
        moveDelay: 0,
        onmovement: null,
        speed: 7.5,
        draw: function () {
            ctx.fillStyle = this.color;
            ctx.fillRect(this.x, this.y, this.width, this.height);
        },
        move: function (){
            ia();
            if (this.onmovement === "up" && this.y > 0) {
                this.y -= this.speed;
            }
            if (this.onmovement === "down" && this.y + this.height < canvas.height) {
                this.y += this.speed;
            }
        }
    };
    
    setCanvasSize();
    
    function ia() {
        if (paddleRight.moveDelay > 0) {
            paddleRight.moveDelay--;
            return;
        }
        var paddlecenter = paddleRight.y + paddleRight.height / 2;
        var tolerance = 5;
        if (Math.abs(paddlecenter - ball.futureY) > tolerance) { 
            if (paddlecenter < ball.futureY) {
                paddleRight.onmovement = "down";
            } else {
                paddleRight.onmovement = "up";
            }
        } else {
            paddleRight.onmovement = "";
        }
    }
    

    function resetBall(player) {
        ball.x = canvas.width / 2;
        ball.y = canvas.height / 2;
        ball.speed = 1.5;
        ball.vx = (player === 1 ? -2 : 2); // Change la direction selon le joueur
        ball.vy = Math.random() * 2 - 1; // Ajoute une variation en Y
        if (player === 1) {
            score1++;
        } else {
            score2++;
        }
        calcPaddleRight();
    }
    
    function checkCollisionRight(){
        let relativeImpact = (ball.y - (paddleRight.y + paddleRight.height / 2)) / (paddleRight.height / 2);
        let maxAngle = Math.PI / 4;
        let angle = relativeImpact * maxAngle;
        ball.vy = ball.speed * Math.sin(angle);
        ball.vx = -ball.speed * Math.cos(angle);
        ball.speed *= 1.1;
        ball.futureY = canvas.height / 2;
    }
    
    function checkCollisionLeft(){
        let relativeImpact = (ball.y - (paddleLeft.y + paddleLeft.height / 2)) / (paddleLeft.height / 2);
        let maxAngle = Math.PI / 4;
        let angle = relativeImpact * maxAngle;
        ball.vy = ball.speed * Math.sin(angle);
        ball.vx = ball.speed * Math.cos(angle);
        ball.speed *= 1.1;
        paddleRight.moveDelay = (canvas.width / 6) / difficulty; // Adjust this value to set the delay
        calcPaddleRight();
    }
    
    window.addEventListener("keyup", function (e) {
        // Reset the paddle movement flags when keys are released
        if (e.key === 'ArrowUp') keyArrowUp = false;
        if (e.key === 'ArrowDown') keyArrowDown = false;
        updatemovements();
    });
    
    window.addEventListener("keydown", function (e) {
        // Set the flags when keys are pressed
        if (e.key === 'ArrowUp') keyArrowUp = true;
        if (e.key === 'ArrowDown') keyArrowDown = true;
        updatemovements();
    });
    
    function updatemovements(){
        if (keyArrowUp && !keyArrowDown) {
            paddleLeft.onmovement = "up";
        }
        if (keyArrowDown && !keyArrowUp) {
            paddleLeft.onmovement = "down";
        }
        if (keyArrowDown && keyArrowUp || !keyArrowDown && !keyArrowUp) {
            paddleLeft.onmovement = false;
        }
    }
    
    function draw() {
        if (!runIA)
            return 1;
        if (score1 === 3 || score2 === 3)
        {
            displayWin()
            return 1;
        }
        clearscreen();
        drawLines();
        drawScore();
        ball.move();
        paddleLeft.move();
        paddleRight.move();
        ball.draw();
        paddleLeft.draw();
        paddleRight.draw();
        animationFrameId = requestAnimationFrame(draw);
        runIA=true;
    }
    
    function displayWin(){
        clearscreen();
        var toprint;
        if (score1 === 3)
            toprint = "PLAYER WIN";
        else
            toprint = "IA WIN";
        const fontsize = Math.min(canvas.width, canvas.height) * 0.25; // Dynamic font size
        ctx.fillStyle = '#d1f7ff';  // Score color
        ctx.font = fontsize + 'px Arial';
        var toprintWidth = ctx.measureText(toprint).width;
        var toprintX = (canvas.width / 2) - (toprintWidth / 2);
        var toprintY = canvas.height / 2 + fontsize / 4;
        ctx.fillText(toprint, toprintX, toprintY);
    }

    function clearscreen() {
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
        errorMargin = canvas.height * (0.1 / difficulty) * 1.5;
        scaleFactor =  Math.sqrt(canvas.width ** 2 + canvas.height ** 2) / 1000;
    }
    
    function calcPaddleRight(){
        ball.futureY = ball.y + ((paddleRight.x - ball.x) * ball.vy / ball.vx);
        ball.futureY += Math.random() * errorMargin - errorMargin / 2;
        while (ball.futureY < 0 || ball.futureY > canvas.height) {
            ball.futureY = ball.futureY < 0 ? -ball.futureY : 2 * canvas.height - ball.futureY;
        }
    }
    
    function initYvals(){
        paddleLeft.y = canvas.height / 2 - canvas.height / 8;
        ball.y = canvas.height / 2;
        ball.x = canvas.width / 2;
        calcPaddleRight();
    }
    
    function startClickHandler() {
        start.addEventListener("click", function(){
            start.style.display = "none";
            stop.style.display = "inline-block";
            initYvals();
            canvas.style.display = "inline-block";
            document.getElementById("difficulty").style.display = "none";
            runIA=true;
            draw();
        });
    }
    
    function resetGame() {
        score1 = 0;
        score2 = 0;
        clearscreen();
    }
    
    function cleanupPong() {
        if (runIA) {
            cancelAnimationFrame(animationFrameId);
            runIA = false;
        }
    
        // Réinitialiser le canvas
        ctx.fillStyle = "#005678";
        ctx.fillRect(0, 0, canvas.width, canvas.height);
    
        // Réinitialiser les scores et la position des éléments
        score1 = 0;
        score2 = 0;
        ball.x = canvas.width / 2;
        ball.y = canvas.height / 2;
        paddleLeft.y = canvas.height / 2 - paddleLeft.height / 2;
        paddleRight.y = canvas.height / 2 - paddleRight.height / 2;
    
        // Cacher l'interface de jeu et afficher les boutons initiaux
        canvas.style.display = "none";
        stop.style.display = "none";
        start.style.display = "inline-block";
        document.getElementById("difficulty").style.display = "inline-block";
    
        // Nettoyer les écouteurs d'événements (si nécessaire)
        document.removeEventListener("click", startClickHandler);
        document.removeEventListener("click", stopClickHandler);
        document.removeEventListener("keydown", updatemovements);
        document.removeEventListener("keyup", updatemovements);
    };
    
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

    function stopClickHandler(){
        stop.addEventListener("click", function(){
            if (runIA == true){
                cancelAnimationFrame(animationFrameId);
                runIA = false;
            }
            ctx.fillStyle = "#005678";
            ctx.fillRect(0, 0, canvas.width, canvas.height);
            resetGame(); // Reset the game
            score1 = 0;
            score2 = 0;
            canvas.style.display = "none";
            stop.style.display = "none";
            start.style.display = "inline-block";
            document.getElementById("difficulty").style.display = "none";
            runIA=false;
            cleanupPong(); // Call cleanup function if the script provides it
            FetchPongHTML();
            return 1;
        });
    }
    
    window.addEventListener("resize", () => {
        const wasRunning = runIA;
        if (wasRunning) {
            cancelAnimationFrame(animationFrameId);
        }
        setCanvasSize();
        if (wasRunning) {
            draw();
        }
    });
    
    stopClickHandler();
    startClickHandler();
}