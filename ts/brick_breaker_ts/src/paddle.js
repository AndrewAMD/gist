var Paddle = (function () {
    function Paddle(game) {
        this.gameWidth = game.gameWidth;
        this.width = 150;
        this.height = 20;
        this.maxSpeed = 7;
        this.speed = 0;
        this.position = {
            x: game.gameWidth / 2 - this.width / 2,
            y: game.gameHeight - this.height - 10,
        };
    }
    Paddle.prototype.moveLeft = function () {
        this.speed = -this.maxSpeed;
    };
    Paddle.prototype.moveRight = function () {
        this.speed = this.maxSpeed;
    };
    Paddle.prototype.stop = function () {
        this.speed = 0;
    };
    Paddle.prototype.draw = function (ctx) {
        ctx.fillStyle = '#0ff';
        ctx.fillRect(this.position.x, this.position.y, this.width, this.height);
    };
    Paddle.prototype.update = function (deltaTime) {
        this.position.x += this.speed;
        if (this.position.x < 0)
            this.position.x = 0;
        if (this.position.x + this.width > this.gameWidth)
            this.position.x = this.gameWidth - this.width;
    };
    return Paddle;
}());
