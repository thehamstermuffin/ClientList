#include "rss-item.h"
#include <QTextStream>
#include <utilities/xml-helper.h>

using namespace cm::utilities;

namespace cm {
namespace rss {

class RssItem::Implementation
{
public:
    Implementation(RssItem* _rssItem)
        : rssItem(_rssItem)
    {
    }

    RssItem* rssItem{nullptr};

    QString description; //This or title mandatory
    QString link; //Optional. Link to full story
    QDateTime pubDate; // Optional. when the item was published
    QString title; //This or description mandatory

    void update(const QDomNode& domNode)
    {
        for (auto i = 0; i < domNode.childNodes().size(); ++i) {
            QDomNode childNode = domNode.childNodes().at(i);
            if (childNode.nodeName() == "description") {
                description = XmlHelper::toString(childNode);
            }
        }
        QDomElement itemTitle = domNode.firstChildElement("title");
        if (!itemTitle.isNull()) {
            title = itemTitle.text();
        }
        QDomElement itemLink = domNode.firstChildElement("link");
        if (!itemLink.isNull()) {
            link = itemLink.text();
        }
        QDomElement itemPubDate = domNode.firstChildElement("pubDate");
        if (!itemPubDate.isNull()) {
            pubDate = QDateTime::fromString(itemPubDate.text(), Qt::RFC2822Date);
        }
    }
};

RssItem::RssItem(QObject *parent, const QDomNode &domNode)
{
    implementation.reset(new Implementation(this));
    implementation->update(domNode);
}

RssItem::~RssItem()
{
}

const QString &RssItem::description() const
{
    return implementation->description;
}

const QString &RssItem::link() const
{
    return implementation->link;
}

const QDateTime &RssItem::pubDate() const
{
    return implementation->pubDate;
}

const QString &RssItem::title() const
{
    return implementation->title;
}

}}
