var InputHandler = (function () {
    function InputHandler(game) {
        document.addEventListener('keydown', function (event) {
            switch (event.key) {
                case "ArrowLeft":
                    game.paddle.moveLeft();
                    break;
                case "ArrowRight":
                    game.paddle.moveRight();
                    break;
                case "Escape":
                    game.togglePause();
                    break;
                case " ":
                    game.start();
                    break;
            }
        });
        document.addEventListener('keyup', function (event) {
            switch (event.key) {
                case "ArrowLeft":
                    if (game.paddle.speed < 0)
                        game.paddle.stop();
                    break;
                case "ArrowRight":
                    if (game.paddle.speed > 0)
                        game.paddle.stop();
                    break;
            }
        });
    }
    return InputHandler;
}());
