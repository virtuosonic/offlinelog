#include "onlinetest.h"

using namespace std::literals;

const QUrl gstatic204_url("http://www.gstatic.com/generate_204");
const QUrl cloudflare204("http://cp.cloudflare.com/generate_204");


OnlineTest::OnlineTest(QObject *parent) :
	QObject{parent},
	_manager(this),
	_restmanager(&_manager,this),
	m_timer(new QTimer(this))
{
	connect(m_timer, &QTimer::timeout,
			this, &OnlineTest::gstatic204);
	m_timer->setSingleShot(true);
	m_timer->start(10s);
}

void OnlineTest::gstatic204()
{
	QNetworkRequest request(gstatic204_url);
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
	request.setTransferTimeout(5s);
	request.setRawHeader("User-Agent", "OfflineLog/1.0");

	_restmanager.get(request,this,[=](QRestReply &reply)
	{
		auto ok = reply.httpStatus() == 204;
		emit online(ok);
		m_timer->start(ok ? 10s : 2s);
	});
}
