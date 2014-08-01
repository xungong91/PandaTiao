/**
 * Created by gx on 2014/7/28.
 */
var GameScene = cc.Scene.extend({
    onEnter : function()
    {
        this._super();


        cc.log("12312");
        gGameLayer = new GameLayer();
        this.addChild(gGameLayer);

        var bg = new cc.Sprite(res.bg);
        bg.attr({
            anchorX: 0.5,
            anchorY: 0.5,
            x: cc.winSize.width / 2,
            y: cc.winSize.height / 2
        });
        //this.addChild(bg);

    }
});

