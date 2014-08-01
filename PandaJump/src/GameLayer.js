/**
 * Created by gx on 2014/7/30.
 */

var gGameLayer;

var GameLayer = cc.Layer.extend({
    mPandaBatchNode:null,
    ctor: function() {
        cc.log("GameLayer init");
        this._super();

        cc.spriteFrameCache.addSpriteFrames(res.panda_plist);
        var pandaTexture = cc.textureCache.addImage(res.panda_png);
        mPandaBatchNode = cc.SpriteBatchNode.create(pandaTexture);
        //mPandaBatchNode.setBlendFunc(cc.SRC_ALPHA, cc.ONE);
        this.addChild(mPandaBatchNode);

        var animFrames = [];
        var str = "";
        for (var i = 0; i < 8; i++) {
            str = "runPanda" + i + ".png";
            var frame = cc.spriteFrameCache.getSpriteFrame(str);
            animFrames.push(frame);
        }
        var animation = cc.Animation.create(animFrames, 0.08);
        cc.animationCache.addAnimation(animation, "Run");

        var panda = new cc.Sprite(cc.spriteFrameCache.getSpriteFrame("runPanda0.png"));
        panda.attr({
            anchorX: 0.5,
            anchorY: 0.5,
            x: cc.winSize.width / 2,
            y: cc.winSize.height / 2
        });
        mPandaBatchNode.addChild(panda);
        panda.runAction(cc.RepeatForever.create(
            cc.Animate.create(animation)));
    }
});