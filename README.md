![status](https://github.com/alxbilger/JsonReader/actions/workflows/ci.yml/badge.svg)
[![docs](https://github.com/alxbilger/JsonReader/actions/workflows/doc.yml/badge.svg)](https://alxbilger.github.io/JsonReader/)

<p align="center">
 <img width="467px" height="200px" src="https://raw.githubusercontent.com/alxbilger/JsonReader/main/JsonReader-logo.png" align="center" alt="JsonReader" />
 <h2 align="center">JsonReader</h2>
 <p align="center">SOFA plugin adding the ability to read SOFA scenes written in the json format</p>
</p>

# Usage

```
runSofa -l JsonReader path/to/scene.json
```

# Examples

Examples are provided in the `scenes` folder.
A SOFA scene written in json looks like:

```json
{
  "Node": {
    "name": "root",
    "dt": "0.02",
    "gravity": "0 -10 0",
    "printLog": "true",
    "Node": {
      "name": "plugins",
      "RequiredPlugin":[
        {"name":"Sofa.Component.Constraint.Projective"},
        {"name":"Sofa.Component.Engine.Select"},
        {"name":"Sofa.Component.LinearSolver.Direct"},
        {"name":"Sofa.Component.Mass"},
        {"name":"Sofa.Component.ODESolver.Backward"},
        {"name":"Sofa.Component.SolidMechanics.FEM.Elastic"},
        {"name":"Sofa.Component.StateContainer"},
        {"name":"Sofa.Component.Topology.Container.Grid"},
        {"name":"Sofa.Component.Visual"}
      ]
    },
    "VisualStyle": { "displayFlags": "showBehaviorModels showForceFields" },
    "DefaultAnimationLoop": { "name": "animationLoop" },
    "DefaultVisualManagerLoop": { "name": "visualLoop" },
    "EulerImplicitSolver": {
      "name": "odesolver",
      "rayleighStiffness": "0.1",
      "rayleighMass": "0.1"
    },
    "MechanicalObject": { "name": "DoFs" },
    "UniformMass": {
      "name": "mass",
      "totalMass": "320"
    },
    "RegularGridTopology": {
      "name": "grid",
      "nx": "4",
      "ny": "4",
      "nz": "20",
      "xmin": "9",
      "xmax": "6",
      "ymin": "0",
      "ymax": "3",
      "zmin": "0",
      "zmax": "19"
    },
    "BoxROI": {
      "name": "box",
      "box": "10 -1 -0.0001  -5 4 0.0001"
    },
    "FixedConstraint": { "indices": "@box.indices" },
    "EigenSimplicialLDLT": {
      "template": "CompressedRowSparseMatrixMat3x3d",
      "ordering": "Natural"
    },
    "HexahedronFEMForceField": {
      "name": "FEM",
      "youngModulus": "4000",
      "poissonRatio": "0.3",
      "method": "large"
    }
  }
}
```

# Compilation

See documentation on the SOFA website to compile an external plugin: https://www.sofa-framework.org/community/doc/plugins/build-a-plugin-from-sources/

## Dependencies

Only SOFA is a dependency
