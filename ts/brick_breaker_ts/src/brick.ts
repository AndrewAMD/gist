class Brick{
    game: Game;
    image: HTMLImageElement;
    position: { x: number, y: number};
    width: number;
    height: number;
    markedForDeletion: boolean;

    constructor(game: Game, position: {x: number, y:number}){
        this.game = game;
        this.image = <HTMLImageElement>document.getElementById("img_brick");

        this.position = position;
        this.width = 80;
        this.height = 24;

        this.markedForDeletion = false;
    }

    update(){
        if (detectCollision(this.game.ball, this)){
            this.game.ball.speed.y = -this.game.ball.speed.y;

            this.markedForDeletion = true;
        }
    }

    draw(ctx: CanvasRenderingContext2D){
        ctx.drawImage(
            this.image, 
            this.position.x,
            this.position.y,
            this.width,
            this.height
            );
    }

}