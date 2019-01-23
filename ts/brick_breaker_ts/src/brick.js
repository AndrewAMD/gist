var Brick = (function () {
    function Brick(game, position) {
        this.game = game;
        this.image = document.getElementById("img_brick");
        this.position = position;
        this.width = 80;
        this.height = 24;
        this.markedForDeletion = false;
    }
    Brick.prototype.update = function () {
        if (detectCollision(this.game.ball, this)) {
            this.game.ball.speed.y = -this.game.ball.speed.y;
            this.markedForDeletion = true;
        }
    };
    Brick.prototype.draw = function (ctx) {
        ctx.drawImage(this.image, this.position.x, this.position.y, this.width, this.height);
    };
    return Brick;
}());
