class InputHandler {
    constructor(game: Game) {
        document.addEventListener('keydown', event => {
            //alert(event.keyCode);
            switch (event.key) {
                case "ArrowLeft": // left key
                    game.paddle.moveLeft();
                    break;
                case "ArrowRight": // right key
                    game.paddle.moveRight();
                    break;
                case "Escape": // escape key
                    game.togglePause();
                    break;
                case " ": // space bar
                    //console.log("spacebar!!");
                    game.start();
                    break;
            }
        });

        document.addEventListener('keyup', event => {
            //alert(event.keyCode);
            switch (event.key) {
                case "ArrowLeft": // left key
                    if (game.paddle.speed < 0)
                        game.paddle.stop();
                    break;
                case "ArrowRight": // right key
                    if (game.paddle.speed > 0)
                        game.paddle.stop();
                    break;
            }
        });

    }
}