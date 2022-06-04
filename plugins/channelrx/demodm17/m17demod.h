///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2022 F4EXB                                                      //
// written by Edouard Griffiths                                                  //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
// (at your option) any later version.                                           //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#ifndef INCLUDE_M17DEMOD_H
#define INCLUDE_M17DEMOD_H

#include <vector>

#include <QNetworkRequest>

#include "dsp/basebandsamplesink.h"
#include "channel/channelapi.h"
#include "util/message.h"

#include "m17demodsettings.h"
#include "m17demodbaseband.h"

class QNetworkAccessManager;
class QNetworkReply;
class QThread;
class DownChannelizer;
class ObjectPipe;

class M17Demod : public BasebandSampleSink, public ChannelAPI {
public:
    class MsgConfigureM17Demod : public Message {
        MESSAGE_CLASS_DECLARATION

    public:
        const M17DemodSettings& getSettings() const { return m_settings; }
        bool getForce() const { return m_force; }

        static MsgConfigureM17Demod* create(const M17DemodSettings& settings, bool force)
        {
            return new MsgConfigureM17Demod(settings, force);
        }

    private:
        M17DemodSettings m_settings;
        bool m_force;

        MsgConfigureM17Demod(const M17DemodSettings& settings, bool force) :
            Message(),
            m_settings(settings),
            m_force(force)
        { }
    };

    M17Demod(DeviceAPI *deviceAPI);
	virtual ~M17Demod();
	virtual void destroy() { delete this; }
    virtual void setDeviceAPI(DeviceAPI *deviceAPI);
    virtual DeviceAPI *getDeviceAPI() { return m_deviceAPI; }

    using BasebandSampleSink::feed;
    virtual void feed(const SampleVector::const_iterator& begin, const SampleVector::const_iterator& end, bool po);
	virtual void start();
	virtual void stop();
    virtual void pushMessage(Message *msg) { m_inputMessageQueue.push(msg); }
    virtual QString getSinkName() { return objectName(); }

    virtual void getIdentifier(QString& id) { id = objectName(); }
    virtual QString getIdentifier() const { return objectName(); }
    virtual void getTitle(QString& title) { title = m_settings.m_title; }
    virtual qint64 getCenterFrequency() const { return m_settings.m_inputFrequencyOffset; }
    virtual void setCenterFrequency(qint64 frequency);

    virtual QByteArray serialize() const;
    virtual bool deserialize(const QByteArray& data);

    virtual int getNbSinkStreams() const { return 1; }
    virtual int getNbSourceStreams() const { return 0; }

    virtual qint64 getStreamCenterFrequency(int streamIndex, bool sinkElseSource) const
    {
        (void) streamIndex;
        (void) sinkElseSource;
        return m_settings.m_inputFrequencyOffset;
    }

    virtual int webapiSettingsGet(
            SWGSDRangel::SWGChannelSettings& response,
            QString& errorMessage);

    virtual int webapiWorkspaceGet(
            SWGSDRangel::SWGWorkspaceInfo& response,
            QString& errorMessage);

    virtual int webapiSettingsPutPatch(
            bool force,
            const QStringList& channelSettingsKeys,
            SWGSDRangel::SWGChannelSettings& response,
            QString& errorMessage);

    virtual int webapiReportGet(
            SWGSDRangel::SWGChannelReport& response,
            QString& errorMessage);

    static void webapiFormatChannelSettings(
        SWGSDRangel::SWGChannelSettings& response,
        const M17DemodSettings& settings);

    static void webapiUpdateChannelSettings(
            M17DemodSettings& settings,
            const QStringList& channelSettingsKeys,
            SWGSDRangel::SWGChannelSettings& response);

    uint32_t getNumberOfDeviceStreams() const;
	void setScopeXYSink(BasebandSampleSink* sampleSink) { m_basebandSink->setScopeXYSink(sampleSink); }
	void configureMyPosition(float myLatitude, float myLongitude) { m_basebandSink->configureMyPosition(myLatitude, myLongitude); }
	double getMagSq() { return m_basebandSink->getMagSq(); }
	bool getSquelchOpen() const { return m_basebandSink->getSquelchOpen(); }
    void getMagSqLevels(double& avg, double& peak, int& nbSamples) { m_basebandSink->getMagSqLevels(avg, peak, nbSamples); }
    int getAudioSampleRate() const { return m_basebandSink->getAudioSampleRate(); }

    static const char* const m_channelIdURI;
    static const char* const m_channelId;

private:
	DeviceAPI *m_deviceAPI;
    QThread *m_thread;
    M17DemodBaseband *m_basebandSink;
	M17DemodSettings m_settings;
    int m_basebandSampleRate; //!< stored from device message used when starting baseband sink

    QNetworkAccessManager *m_networkManager;
    QNetworkRequest m_networkRequest;

    static const int m_udpBlockSize;

	virtual bool handleMessage(const Message& cmd);
    void applySettings(const M17DemodSettings& settings, bool force = false);
    void sendSampleRateToDemodAnalyzer();
    void webapiFormatChannelReport(SWGSDRangel::SWGChannelReport& response);
    void webapiReverseSendSettings(QList<QString>& channelSettingsKeys, const M17DemodSettings& settings, bool force);
    void sendChannelSettings(
        const QList<ObjectPipe*>& pipes,
        QList<QString>& channelSettingsKeys,
        const M17DemodSettings& settings,
        bool force
    );
    void webapiFormatChannelSettings(
        QList<QString>& channelSettingsKeys,
        SWGSDRangel::SWGChannelSettings *swgChannelSettings,
        const M17DemodSettings& settings,
        bool force
    );

private slots:
    void networkManagerFinished(QNetworkReply *reply);
    void handleIndexInDeviceSetChanged(int index);
};

#endif // INCLUDE_M17DEMOD_H