/**
 * SDRangel
 * This is the web REST/JSON API of SDRangel SDR software. SDRangel is an Open Source Qt5/OpenGL 3.0+ (4.3+ in Windows) GUI and server Software Defined Radio and signal analyzer in software. It supports Airspy, BladeRF, HackRF, LimeSDR, PlutoSDR, RTL-SDR, SDRplay RSP1 and FunCube    ---   Limitations and specifcities:    * In SDRangel GUI the first Rx device set cannot be deleted. Conversely the server starts with no device sets and its number of device sets can be reduced to zero by as many calls as necessary to /sdrangel/deviceset with DELETE method.   * Preset import and export from/to file is a server only feature.   * Device set focus is a GUI only feature.   * The following channels are not implemented (status 501 is returned): ATV and DATV demodulators, Channel Analyzer NG, LoRa demodulator   * The device settings and report structures contains only the sub-structure corresponding to the device type. The DeviceSettings and DeviceReport structures documented here shows all of them but only one will be or should be present at a time   * The channel settings and report structures contains only the sub-structure corresponding to the channel type. The ChannelSettings and ChannelReport structures documented here shows all of them but only one will be or should be present at a time    --- 
 *
 * OpenAPI spec version: 4.2.0
 * Contact: f4exb06@gmail.com
 *
 * NOTE: This class is auto generated by the swagger code generator program.
 * https://github.com/swagger-api/swagger-codegen.git
 * Do not edit the class manually.
 */

/*
 * SWGBladeRF1OutputSettings.h
 *
 * BladeRF1
 */

#ifndef SWGBladeRF1OutputSettings_H_
#define SWGBladeRF1OutputSettings_H_

#include <QJsonObject>



#include "SWGObject.h"
#include "export.h"

namespace SWGSDRangel {

class SWG_API SWGBladeRF1OutputSettings: public SWGObject {
public:
    SWGBladeRF1OutputSettings();
    SWGBladeRF1OutputSettings(QString* json);
    virtual ~SWGBladeRF1OutputSettings();
    void init();
    void cleanup();

    virtual QString asJson () override;
    virtual QJsonObject* asJsonObject() override;
    virtual void fromJsonObject(QJsonObject &json) override;
    virtual SWGBladeRF1OutputSettings* fromJson(QString &jsonString) override;

    qint64 getCenterFrequency();
    void setCenterFrequency(qint64 center_frequency);

    qint32 getDevSampleRate();
    void setDevSampleRate(qint32 dev_sample_rate);

    qint32 getVga1();
    void setVga1(qint32 vga1);

    qint32 getVga2();
    void setVga2(qint32 vga2);

    qint32 getBandwidth();
    void setBandwidth(qint32 bandwidth);

    qint32 getLog2Interp();
    void setLog2Interp(qint32 log2_interp);

    qint32 getXb200();
    void setXb200(qint32 xb200);

    qint32 getXb200Path();
    void setXb200Path(qint32 xb200_path);

    qint32 getXb200Filter();
    void setXb200Filter(qint32 xb200_filter);


    virtual bool isSet() override;

private:
    qint64 center_frequency;
    bool m_center_frequency_isSet;

    qint32 dev_sample_rate;
    bool m_dev_sample_rate_isSet;

    qint32 vga1;
    bool m_vga1_isSet;

    qint32 vga2;
    bool m_vga2_isSet;

    qint32 bandwidth;
    bool m_bandwidth_isSet;

    qint32 log2_interp;
    bool m_log2_interp_isSet;

    qint32 xb200;
    bool m_xb200_isSet;

    qint32 xb200_path;
    bool m_xb200_path_isSet;

    qint32 xb200_filter;
    bool m_xb200_filter_isSet;

};

}

#endif /* SWGBladeRF1OutputSettings_H_ */
