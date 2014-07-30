/**
 * Created by gx on 2014/7/28.
 */
var GameScene = cc.Scene.extend({
    onEnter : function()
    {
        this._super();

        gBackgroundLayer = new BackgroundLayer();
        this.addChild(gBackgroundLayer);

        gGameLayer = new GameLayer();
        this.addChild(gGameLayer);
    }
});

