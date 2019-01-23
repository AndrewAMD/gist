class Ball{
    game: Game;
    gameWidth: number;
    gameHeight: number;
    image: HTMLImageElement;
    size: number;
    position: { x: number, y: number };
    speed: { x: number, y: number };

    constructor(game: Game){
        this.game = game;
        this.gameWidth = game.gameWidth;
        this.gameHeight = game.gameHeight;
        this.image = <HTMLImageElement>document.getElementById("img_ball");

        this.size = 16
        this.reset();
    }


    reset(){
        this.position = {
            x: 10,
            y: 400,
        };
        this.speed = {
            x: 4,
            y: -2,
        };
    }

    draw(ctx: CanvasRenderingContext2D){
        ctx.drawImage(
            this.image, 
            this.position.x,
            this.position.y,
            this.size,
            this.size
            );
    }

    update(deltaTime){
        
        this.position.x += this.speed.x;
        this.position.y += this.speed.y;

        let bottomOfBall = this.position.y + this.size;
        let rightOfBall = this.position.x + this.size;

        // wall on left or right of screen
        if(rightOfBall > this.gameWidth || this.position.x < 0){
            this.speed.x = -this.speed.x;
        }
        // wall on top
        if(this.position.y < 0){
            this.speed.y = -this.speed.y;
        }

        // bottom of screen
        if(bottomOfBall > this.gameHeight){
            this.game.lives--;
            this.reset();
        }


        if(detectCollision(this,this.game.paddle)){
            this.speed.y = -this.speed.y;
            this.position.y = this.game.paddle.position.y - this.size;
        }
        
    }
}