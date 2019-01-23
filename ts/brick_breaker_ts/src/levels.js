function buildLevel(game, level) {
    var bricks = [];
    level.forEach(function (row, rowIndex) {
        row.forEach(function (brick, brickIndex) {
            if (brick === 1) {
                var position = {
                    x: 80 * brickIndex,
                    y: 75 + 24 * rowIndex
                };
                bricks.push(new Brick(game, position));
            }
        });
    });
    return bricks;
}
var level1 = [
    [0, 0, 0, 0, 0, 0, 0, 0, 1, 0],
];
var level2 = [
    [0, 1, 1, 0, 0, 0, 0, 1, 1, 0],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
];
