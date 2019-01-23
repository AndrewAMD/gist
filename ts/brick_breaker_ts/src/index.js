var canvas = document.getElementById("gameScreen");
var ctx = canvas.getContext('2d');
var GAME_WIDTH = 800;
var GAME_HEIGHT = 600;
var game = new Game(GAME_WIDTH, GAME_HEIGHT);
var lastTime = 0;
function gameLoop(timestamp) {
    var deltaTime = timestamp - lastTime;
    lastTime = timestamp;
    ctx.clearRect(0, 0, GAME_WIDTH, GAME_HEIGHT);
    game.update(deltaTime);
    game.draw(ctx);
    requestAnimationFrame(gameLoop);
}
requestAnimationFrame(gameLoop);
