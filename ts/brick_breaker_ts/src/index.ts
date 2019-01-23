let canvas = <HTMLCanvasElement> document.getElementById("gameScreen");
let ctx = <CanvasRenderingContext2D > canvas.getContext('2d');

const GAME_WIDTH = 800;
const GAME_HEIGHT = 600;

let game = new Game(GAME_WIDTH, GAME_HEIGHT);

let lastTime: DOMHighResTimeStamp = 0;

function gameLoop(timestamp: DOMHighResTimeStamp){
    let deltaTime: DOMHighResTimeStamp = timestamp - lastTime;
    lastTime = timestamp;

    ctx.clearRect(0,0,GAME_WIDTH,GAME_HEIGHT); // clear canvas

    game.update(deltaTime);
    game.draw(ctx);

    requestAnimationFrame(gameLoop);
}

requestAnimationFrame(gameLoop);
