
function buildLevel(game: Game, level: number[][]){
    let bricks = [];
    level.forEach((row: number[], rowIndex: number) => {
        row.forEach((brick: number, brickIndex: number) => {
            
            if (brick === 1){
                let position = {
                    x: 80 * brickIndex, 
                    y: 75 + 24 * rowIndex
                };
                bricks.push(new Brick(game, position));
            }
            
        });
    });

    return bricks;
}

const level1 = [
    [0,0,0,0,0,0,0,0,1,0],
    // [1,1,1,1,1,1,1,1,1,1],
    // [1,1,1,1,1,1,1,1,1,1],
    // [1,1,1,1,1,1,1,1,1,1]
];


const level2 = [
    [0,1,1,0,0,0,0,1,1,0],
    [1,1,1,1,1,1,1,1,1,1],
    [1,1,1,1,1,1,1,1,1,1],
    [1,1,1,1,1,1,1,1,1,1]
];