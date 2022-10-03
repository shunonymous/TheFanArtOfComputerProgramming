// シスター・クレアの謎配信ジェネレーター
// クレアさんがやってそうでやってない、でもやってるかもしれない配信のタイトルを生成するよ!
// 君だけの最強のシスター・クレアの配信タイトルを作ろう!(?)
//
// Authored by Shun Terabayashi <shunonymous@gmail.com>

#include <iostream>
#include <random>
#include <string>
#include <string_view>

class StreamTitleGenerator
{
private:
    // 配信のカテゴリ。ゲームとか歌枠とか。
    enum class StreamType : int
    {
        GAME,
        TALK,
        SINGING,
        RADIO,
        WORKING,
        end
    };

    // ゲーム配信だった場合のゲーム。
    const std::vector<std::string_view> games = {"マイクラ",
                                                 "テトリス",
                                                 "ゴッドフィールド",
                                                 "ポケモンスナップ",
                                                 "あつ森",
                                                 "雀魂",
                                                 "アソビ大全",
                                                 "ホラー",
                                                 "トラック",
                                                 "ふぉーるがいず",
                                                 "APEX",
                                                 "壺おじさん",
                                                 "リングフィットアドベンチャー",
                                                 "リズム天国"};

    // ランダム生成機
    std::random_device seed_gen;
    std::mt19937       engine;

    // ランダムに配信内容を決める
    bool             isDanger();
    bool             isFPS(); // 勿論Foot Pressure Point(足つぼ)の意
    bool             isBathRoom();
    bool             isSleeping();
    bool             isBinaural();
    StreamType       getKindOfStream();
    std::string_view getGame();

public:
    std::string genStream();

    StreamTitleGenerator();
    ~StreamTitleGenerator()
    {
    }
};

// 結果次第で何をしでかすかわからない危ない配信になる。ロックだぜ。
bool StreamTitleGenerator::isDanger()
{
    std::bernoulli_distribution dist(0.02);
    bool                        result = dist(engine);

    return result;
}

// 結果次第でクレアさんが足つぼで健康になる。
bool StreamTitleGenerator::isFPS()
{
    std::bernoulli_distribution dist(0.3);
    bool                        result = dist(engine);

    return result;
}

// 結果次第でクレアさんがお風呂から配信する。はわわわ。
bool StreamTitleGenerator::isBathRoom()
{
    std::bernoulli_distribution dist(0.3);
    bool                        result = dist(engine);

    return result;
}

// 結果次第でクレアさんがすやすやする。かわいい。
bool StreamTitleGenerator::isSleeping()
{
    std::bernoulli_distribution dist(0.4);
    bool                        result = dist(engine);

    return result;
}

// 結果次第でクレアさんがバイノーラルマイクで配信する。
bool StreamTitleGenerator::isBinaural()
{
    std::bernoulli_distribution dist(0.3);
    bool                        result = dist(engine);

    return true;
}

// クレアさんがやるゲームをランダムで決める。
std::string_view StreamTitleGenerator::getGame()
{
    std::uniform_int_distribution<> dist(0, games.size() - 1);
    return games[dist(engine)];
}

// 歌枠とかゲーム配信とか雑談とかを決める。たゐき。
StreamTitleGenerator::StreamType StreamTitleGenerator::getKindOfStream()
{
    std::uniform_int_distribution<int> dist(0, static_cast<int>(StreamType::end) - 1);
    StreamType                         type = static_cast<StreamType>(dist(engine));

    return type;
}

// 配信タイトルを生成する。どきどき。
std::string StreamTitleGenerator::genStream()
{
    std::string title = "";
    if (isDanger())
    {
        title.append("何をしでかすかわからない危ない");
    }
    if (isFPS())
    {
        title.append("足つぼ");
    }

    // クレアさんがお風呂で寝ないようにする処理
    bool bathroom = true;
    bool sleeping = true;
    while (bathroom and sleeping)
    {
        bathroom = isBathRoom();
        sleeping = isSleeping();
    }

    if (bathroom)
    {
        title.append("風呂");
    }
    if (sleeping)
    {
        title.append("すやすや");
    }
    if (isBinaural())
    {
        title.append("ばいのーらる");
    }
    switch (getKindOfStream())
    {
    case StreamType::TALK:
        title.append("雑談");
        break;
    case StreamType::SINGING:
        title.append("歌枠");
        break;
    case StreamType::RADIO:
        title.append("ラジオ");
        break;
    case StreamType::WORKING:
        title.append("作業配信");
        break;
    case StreamType::GAME:
        title.append(getGame());
        break;
    default:
        title.append("例外配達");
        throw;
        break;
    }

    return title;
}

StreamTitleGenerator::StreamTitleGenerator()
{
    engine = std::mt19937(seed_gen());
}

int main()
{
    StreamTitleGenerator generator;

    std::cout << generator.genStream() << std::endl;
}
