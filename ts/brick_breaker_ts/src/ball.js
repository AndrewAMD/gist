var Ball = (function () {
    function Ball(game) {
        this.game = game;
        this.gameWidth = game.gameWidth;
        this.gameHeight = game.gameHeight;
        this.image = document.getElementById("img_ball");
        this.size = 16;
        this.reset();
    }
    Ball.prototype.reset = function () {
        this.position = {
            x: 10,
            y: 400,
        };
        this.speed = {
            x: 4,
            y: -2,
        };
    };
    Ball.prototype.draw = function (ctx) {
        ctx.drawImage(this.image, this.position.x, this.position.y, this.size, this.size);
    };
    Ball.prototype.update = function (deltaTime) {
        this.position.x += this.speed.x;
        this.position.y += this.speed.y;
        var bottomOfBall = this.position.y + this.size;
        var rightOfBall = this.position.x + this.size;
        if (rightOfBall > this.gameWidth || this.position.x < 0) {
            this.speed.x = -this.speed.x;
        }
        if (this.position.y < 0) {
            this.speed.y = -this.speed.y;
        }
        if (bottomOfBall > this.gameHeight) {
            this.game.lives--;
            this.reset();
        }
        if (detectCollision(this, this.game.paddle)) {
            this.speed.y = -this.speed.y;
            this.position.y = this.game.paddle.position.y - this.size;
        }
    };
    return Ball;
}());
