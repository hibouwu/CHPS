<div dir="rtl">

<h1>‫محرك MLP والاشتقاق التلقائي لـ MNIST‬</h1>

‫[English](../README.md) | [Français](README_fr.md) | [中文](README_zh.md) | **[العربية](README_ar.md)**‬

‫يحتوي هذا المستودع على تنفيذ كامل لشبكة عصبية متعددة الطبقات (MLP) مكتوبة من الصفر بلغة ++C.‬

‫تم تطويره في إطار مشروع البرمجة العددية (PPN) لمنهج ماستر 1 CHPS _(الحوسبة عالية الأداء والمحاكاة)_ في جامعة باريس-ساكليه (UVSQ).‬

‫الهدف الرئيسي من هذا المشروع هو فهم الآليات الداخلية لأطر التعلم العميق، من خلال تنفيذ محرك اشتقاق تلقائي عكسي مخصص وعمليات مصفوفية محسّنة، دون الاعتماد على مكتبات تعلم آلي خارجية كـ PyTorch أو TensorFlow.‬

---

<h2>‫مميزات المشروع‬</h2>

- ‫**محرك اشتقاق تلقائي مخصص**: تنفيذ رسم بياني ديناميكي للحسابات (DAG) يدعم الاشتقاق التلقائي بالاتجاه العكسي.‬
- ‫**عمليات موترية محسّنة**: نوى ضرب المصفوفات محسّنة باستخدام تقسيم الذاكرة المخبأة (cache blocking)، والمعالجة المتوازية عبر OpenMP، ودعم اختياري لـ BLAS.‬
- ‫**شبكة عصبية قابلة للتهيئة**: دعم تهيئات طبقات عشوائية، ودوال تنشيط (ReLU، LeakyReLU، GELU، Sigmoid، Tanh)، واستراتيجيات تهيئة الأوزان (He، Xavier).‬
- ‫**خط أنابيب التدريب**: حلقة تدريب كاملة مع SGD / MomentumSGD / AdamW، وخسارة CrossEntropy، ومعالجة الدُفعات الصغيرة.‬

---

<h2>‫المتطلبات المسبقة‬</h2>

‫يتطلب المشروع مُصرِّفًا متوافقًا مع C++17 وأداة CMake. يُوصى بـ OpenBLAS للحصول على أفضل أداء.‬

- ‫CMake 3.16 أو أحدث‬
- ‫GCC أو Clang مع دعم C++17‬
- ‫OpenBLAS (اختياري، لكن يُوصى به بشدة)‬

---

<h2>‫التثبيت‬</h2>

<h3>‫Fedora / RHEL‬</h3>

</div>

```bash
sudo dnf install cmake gcc-c++ openblas-devel
```

<div dir="rtl">

<h3>‫Ubuntu / Debian‬</h3>

</div>

```bash
sudo apt install cmake g++ libopenblas-dev
```

<div dir="rtl">

---

<h2>‫البناء والاستخدام‬</h2>

<h3>‫1. التصريف (الافتراضي: بدون تكلفة gprof)‬</h3>

</div>

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=OFF
cmake --build build -j$(nproc)
```

<div dir="rtl">

<h3>‫1.1 البناء المتسلسل مقابل MPI‬</h3>

‫يُنشئ المشروع ملفًا تنفيذيًا واحدًا للتدريب: `ppn_train`. يُفعَّل دعم MPI عند تهيئة CMake عبر `-DENABLE_MPI=ON`، ولا يُنتج اسمًا مختلفًا للملف التنفيذي.‬

**بناء أحادي العملية:**

</div>

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=OFF
cmake --build build -j$(nproc)
```

<div dir="rtl">

‫**بناء موزع مع تفعيل MPI:**‬

</div>

```bash
cmake -S . -B build-mpi -DCMAKE_BUILD_TYPE=Release -DENABLE_MPI=ON
cmake --build build-mpi -j$(nproc)
```

<div dir="rtl">

‫يُنصح باستخدام مجلدات بناء منفصلة مثل `build` و`build-mpi` للاحتفاظ بكلا التهيئتين جنبًا إلى جنب. يُحدَّد خيار `ENABLE_MPI` عند تهيئة CMake، وليس عند `cmake --build`.‬

<h3>‫1.2 بناء التنميط (gprof عند الحاجة فقط)‬</h3>

‫أداة `-pg` معطّلة افتراضيًا. فعّلها صراحةً للتنميط:‬

</div>

```bash
cmake -S . -B build-gprof -DCMAKE_BUILD_TYPE=Release -DENABLE_GPROF=ON
cmake --build build-gprof -j$(nproc)
```

<div dir="rtl">

<h3>‫1.3 بناء VTune مع علامات ITT‬</h3>

‫إذا كانت أداة Intel VTune Profiler وملفات تطوير ITT API متوفرة على جهازك، يكتشفها البناء تلقائيًا ويفعّل علامات المهام للمراحل الرئيسية: `train_epoch`، `train_batch`، `data_loader`، `forward_loss`، `backward`، `gradient_sync`، `optimizer_step`.‬

**البناء الموصى به:**

</div>

```bash
cmake -S . -B build-vtune -DCMAKE_BUILD_TYPE=RelWithDebInfo -DENABLE_VTUNE_MARKERS=ON
cmake --build build-vtune -j$(nproc)
```

<div dir="rtl">

‫إذا لم تُوجد ترويسات أو مكتبة ITT، يُكمل المشروع البناء بشكل طبيعي مع تعطيل علامات VTune.‬

<h3>‫1.4 الواجهة الاختيارية oneDNN لـ Conv‬</h3>

‫يدعم المشروع واجهة خلفية اختيارية oneDNN لطبقة `Conv2DLayer`. غير مفعّلة افتراضيًا ولا تجعل oneDNN تبعيةً إلزامية للمشروع.‬

‫**البناء مع دعم oneDNN Conv:**‬

</div>

```bash
cmake -S . -B build-onednn -DCMAKE_BUILD_TYPE=Release -DENABLE_ONEDNN_CONV_BACKEND=ON
cmake --build build-onednn -j$(nproc)
```

<div dir="rtl">

**اختيار الواجهة الخلفية عند التشغيل:**

</div>

```bash
./build-onednn/ppn_train --model cnn --conv_backend reference
./build-onednn/ppn_train --model cnn --conv_backend onednn
```

<div dir="rtl">

‫إذا طُلبت `--conv_backend onednn` من ملف ثنائي لم يُبنَ مع دعم oneDNN Conv، يفشل بناء النموذج فورًا بدلًا من التراجع الصامت.‬

---

<h2>‫2. تحضير مجموعة البيانات‬</h2>

‫يُوفَّر سكريبت لتنزيل مجموعة بيانات MNIST:‬

</div>

```bash
./scripts/MnistDDataDownload/get_mnist.sh
```

<div dir="rtl">

<h2>‫3. التشغيل‬</h2>

**التدريب بالإعداد الافتراضي:**

</div>

```bash
./build/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

<div dir="rtl">

‫**مع تفعيل MPI:**‬

</div>

```bash
mpiexec -n 4 ./build-mpi/ppn_train --epochs 20 --learning_rate 0.01 --batch_size 64 --hidden_size 128
```

<div dir="rtl">

---

<h2>‫خيارات سطر الأوامر‬</h2>

يدعم التطبيق خيارات سطر الأوامر التالية:

| الخيار | الافتراضي | الوصف |
|---|---|---|
‫| `--epochs` | 1 | عدد دورات التدريب |‬
‫| `--learning_rate` | 0.01 | معدل التعلم |‬
‫| `--batch_size` | 64 | حجم الدُفعة الصغيرة |‬
‫| `--hidden_size` | 128 | حجم طبقة مخفية واحدة |‬
‫| `--hidden_sizes` | `""` | أحجام طبقات مخفية متعددة (مفصولة بفاصلة). تتجاوز `--hidden_size` |‬
‫| `--data_dir` | `"mnist"` | مجلد ملفات MNIST |‬
‫| `--activation` | `relu` | دالة التنشيط (relu/leaky_relu/gelu/sigmoid/tanh) |‬
‫| `--optimizer` | `sgd` | المحسِّن (sgd/momentum_sgd/momentum/adamw) |‬
‫| `--momentum` | 0.9 | معامل الزخم (يستخدمه momentum_sgd) |‬
‫| `--nesterov` | 0 | علم زخم Nesterov (0 أو 1)، يستخدمه momentum_sgd |‬
‫| `--weight_decay` | 0.0 | تراجع الأوزان (يستخدمه momentum_sgd/adamw) |‬
| `--beta1` | 0.9 | AdamW beta1 |
| `--beta2` | 0.999 | AdamW beta2 |
| `--eps` | 1e-8 | AdamW epsilon |
‫| `--init` | `he` | استراتيجية تهيئة الأوزان (he/xavier/manual) |‬
‫| `--seed` | 0 | البذرة العشوائية (0 = عشوائي) |‬
‫| `--conv_backend` | `reference` | واجهة Conv للـ CNN (reference/onednn) |‬

---

<h2>‫السكريبتات المساعدة‬</h2>

‫يحتوي مجلد `scripts/` على أدوات متنوعة للاختبار وتشغيل التجارب:‬

- **الاختبارات المرجعية:**
- ‫`benchmark_matmul.sh`: مقارنة ضرب المصفوفات البسيط مقابل المحسَّن.‬
- ‫`benchmark_e2e.sh`: اختبار أداء التدريب الشامل.‬
- **التجارب:**
- ‫`exp_learning_rate.sh`، `exp_batch_size.sh`، `exp_hidden_size.sh`: مسح المعاملات الفائقة.‬
- ‫`exp_init_comparison.sh`: مقارنة استراتيجيات تهيئة الأوزان.‬
- **التمثيل البصري:**
- ‫سكريبتات Python (مثل `scripts/Utils/plot_metrics.py`) لإنشاء مخططات الأداء.‬

---

<h2>‫إعادة إنتاج الأداء‬</h2>

‫**مقارنة MLP مقابل CNN بإعدادات ثابتة (batch=256, seed=42, MNIST):**‬

</div>

```bash
./scripts/Performance/compare_cnn_mlp.sh
```

<div dir="rtl">

‫ينتج سجلات وملخص CSV في `output/gprof_compare/compare_cnn_mlp.csv`.‬

‫**تشغيل خط أنابيب gprof للـ CNN:**‬

</div>

```bash
./scripts/Performance/run_gprof_cnn.sh
```

<div dir="rtl">

‫ينتج `gmon.*`، `gprof_flat.txt`، و`gprof_callgraph.txt` في `output/gprof/`.‬

‫**تشغيل جمع نقاط VTune الساخنة:**‬

</div>

```bash
source /opt/intel/oneapi/setvars.sh
./scripts/Performance/run_vtune_hotspots.sh --epochs 1 --batch_size 256 --data_dir mnist
```

<div dir="rtl">

‫يُهيِّئ السكريبت بناءً RelWithDebInfo في `build-vtune/`، يُشغّل `vtune -collect hotspots`، ويحفظ النتيجة في `output/vtune/`.‬

---

<h2>‫البنية المعمارية‬</h2>

تتكون بنية الشبكة من رسم بياني ديناميكي للعمليات.

</div>

```
Input (784) -> Linear -> ReLU -> Linear -> Softmax -> Output (10)
```

<div dir="rtl">

‫[عرض مخطط البنية التفصيلي (UML)]‬

---

<h2>‫الأداء‬</h2>

‫تم اختبار التنفيذ على معالج AMD Ryzen. يُظهر الإصدار المحسَّن بـ BLAS تسريعًا ملحوظًا مقارنةً بالتنفيذ البسيط.‬

| التنفيذ | وقت التدريب (لكل دورة) | نسبة التسريع |
|---|---|---|
‫| ++C البسيط | ~60 ثانية | 1x |‬
‫| المحسَّن (BLAS) | ~0.3 ثانية | ~200x |‬

---

<h2>‫التوثيق‬</h2>

- ‫[التقرير التقني (بالفرنسية)](Docs/conception_detaillee_fr.md)‬
- ‫[التصميم التفصيلي](Docs/conception_detaillee_fr.md)‬
- ‫[المتطلبات (بالفرنسية)](Docs/requirements_fr.md)‬

---

<h2>‫المؤلفون‬</h2>

- Jianye Shi
- Hao Qian
- Xiang Bian
- Abdennour Boulmis

‫**المشرف:** Aurélien Delval‬

---

<h2>‫الرخصة‬</h2>

لا يوجد ملف رخصة. هذا المشروع مخصص للاستخدام الأكاديمي والتعليمي فقط.

</div>
