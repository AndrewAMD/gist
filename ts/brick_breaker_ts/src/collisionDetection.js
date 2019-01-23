function detectCollision(ball, gameObject) {
    var bottomOfBall = ball.position.y + ball.size;
    var topOfBall = ball.position.y;
    var rightSideOfBall = ball.position.x + ball.size;
    var topOfObject = gameObject.position.y;
    var leftSideOfObject = gameObject.position.x;
    var rightSideOfObject = gameObject.position.x + gameObject.width;
    var bottomOfObject = gameObject.position.y + gameObject.height;
    if (bottomOfBall >= topOfObject &&
        topOfBall <= bottomOfObject &&
        ball.position.x >= leftSideOfObject &&
        rightSideOfBall <= rightSideOfObject) {
        return true;
    }
    else {
        return false;
    }
}
